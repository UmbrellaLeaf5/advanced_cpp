# language: CMake

include(${REPO_FOLDER}/settings.cmake)

# Libraries
set(GLOBAL_LIBS shape_lib)

# find_library(shape_lib ../)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example_shape_lib/shape_lib)

# Add executable
file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true ".")

string(REPLACE ";" "|" PREFIX "${TASK_PREFIXES}")

foreach(SUBDIR ${SUBDIRS})
  if("${SUBDIR}" MATCHES "${PROJECT_NAME}/(${PREFIX})[^/]*$")
    get_filename_component(SUBPROJECT_NAME ${SUBDIR} NAME)
    set(SUBPROJECT_NAME "${PROJECT_NAME}_${SUBPROJECT_NAME}")

    # (files only in one subfolder)
    file(GLOB SUBPROJECT_SOURCES
      ${SUBDIR}/${HEADERS_FORMAT}
      ${SUBDIR}/${SOURCES_FORMAT}
    )

    add_executable(${SUBPROJECT_NAME} ${SUBPROJECT_SOURCES})

    target_link_libraries(${SUBPROJECT_NAME} PRIVATE ${LIB_NAME} ${GLOBAL_LIBS})
    target_include_directories(${SUBPROJECT_NAME} PRIVATE ${REPO_FOLDER}/${LIB_NAME})
  endif()
endforeach()

target_include_directories("${PROJECT_NAME}_example_shape_lib" PRIVATE example_shape_lib/shape_lib)
