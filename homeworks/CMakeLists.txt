# language: CMake

include(${REPO_FOLDER}/settings.cmake)

# Libraries

# find_package()
# add_library()
set(GLOBAL_LIBS)

# Add executable
file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true ".")

string(REPLACE ";" "|" PREFIX "${TASK_PREFIXES}")

foreach(SUBDIR ${SUBDIRS})
  if("${SUBDIR}" MATCHES "${PROJECT_NAME}/(${PREFIX})[^/]*$")
    get_filename_component(SUBPROJECT_NAME ${SUBDIR} NAME)
    set(SUBPROJECT_NAME "${PROJECT_NAME}_${SUBPROJECT_NAME}")

    # (files only in one subfolder)
    file(GLOB_RECURSE SUBPROJECT_SOURCES
      ${SUBDIR}/${HEADERS_FORMAT}
      ${SUBDIR}/${SOURCES_FORMAT}
    )

    add_executable(${SUBPROJECT_NAME} ${SUBPROJECT_SOURCES})

    target_link_libraries(${SUBPROJECT_NAME} PRIVATE ${LIB_NAME} ${GLOBAL_LIBS})
    target_include_directories(${SUBPROJECT_NAME} PRIVATE ${REPO_FOLDER}/${LIB_NAME})
  endif()
endforeach()
