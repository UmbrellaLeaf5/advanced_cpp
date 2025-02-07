# language: CMake

# ---------------------------------     Project setup      ---------------------------------
cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

# ---------------------------------    Set C++ settings    ---------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++23 -O2")

# less speed, more warnings = less potential errors in code
# flags using source: https://codeforces.com/blog/entry/15547?locale=ru
# set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -std=c++23 -O2 -Wfloat-equal -Wconversion -Wlogical-op -Wduplicated-cond")

# ---------------------------------   Set CMake settings   ---------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ---------------------------------        Libraries        --------------------------------
add_subdirectory(example_shape_lib/shape_lib)

# ---------------------------------      Add executable     --------------------------------
file(GLOB_RECURSE SUBFOLDERS LIST_DIRECTORIES true ".")

find_library(Lib ../)

foreach(SUBDIR ${SUBFOLDERS})
  if(IS_DIRECTORY ${SUBDIR})
    if("${SUBDIR}" MATCHES "${PROJECT_NAME}/(task|example)_[^/]*$")
      get_filename_component(SUBPROJECT_NAME ${SUBDIR} NAME)
      set(SUBPROJECT_NAME "${PROJECT_NAME}_${SUBPROJECT_NAME}")

      # files only in one subfolder
      file(GLOB SUBPROJECT_SOURCES "${SUBDIR}/*.hpp" "${SUBDIR}/*.cpp")

      add_executable(${SUBPROJECT_NAME} ${SUBPROJECT_SOURCES})

      target_link_libraries(${SUBPROJECT_NAME} PRIVATE Lib)
    endif()
  endif()
endforeach()

# ---------------------------------     Copy extra files    --------------------------------
file(GLOB_RECURSE EXTRA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB_RECURSE PROJECT_FILES "*.cpp" "*.h" "*.hpp" "*.sh" "*.o*" "*.e*" "*.md")

list(REMOVE_ITEM EXTRA_FILES ${PROJECT_FILES})

file(COPY ${EXTRA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# ---------------------------------    For this project     --------------------------------
find_library(shape_lib ../)

target_link_libraries("${PROJECT_NAME}_example_shape_lib" PRIVATE shape_lib)
target_include_directories("${PROJECT_NAME}_example_shape_lib" PRIVATE example_shape_lib/shape_lib)