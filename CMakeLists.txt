# language: CMake

cmake_minimum_required(VERSION 3.25)

project(project)
include(.cmake/settings.cmake)

# Lesson folders
file(GLOB_RECURSE DIRS LIST_DIRECTORIES true ".")

string(REPLACE ";" "|" PREFIX "${LESSON_PREFIXES}")

foreach(DIR ${DIRS})
  if(IS_DIRECTORY ${DIR})
    if(${DIR} MATCHES "${PROJECT_NAME}/(${PREFIX})[^/]*$")
      add_subdirectory(${DIR})
    endif()
  endif()
endforeach()

# Library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME})

# Uncomment and install to get icecream-cpp (and comment other add_subdirectory)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}/icecream-cpp)