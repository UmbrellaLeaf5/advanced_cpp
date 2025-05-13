# language: CMake

cmake_minimum_required(VERSION 3.25)

project(project)
include(.cmake/settings.cmake)

# Lesson folders
file(GLOB_RECURSE DIRS LIST_DIRECTORIES true ".")

string(REPLACE ";" "|" PREFIX "${LESSON_PREFIXES}")

set(ICECREAM_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/CMake/icecream-cpp-config.cmake")

if(EXISTS "${ICECREAM_CONFIG_FILE}")
  message(STATUS "Icecream-cpp installed correctly!")

  foreach(DIR ${DIRS})
    if(IS_DIRECTORY ${DIR})
      if(${DIR} MATCHES "${PROJECT_NAME}/(${PREFIX})[^/]*$")
        add_subdirectory(${DIR})
      endif()
    endif()
  endforeach()

  # Library
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME})

else()
  message(STATUS "Icecream-cpp not installed...")
  message(WARNING "Please, install icecream-cpp with `cmake --install <build_directory>`")

  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}/icecream-cpp)
endif()
