# CMAKE tutorial:
#   https://tuannguyen68.gitbooks.io/learning-cmake-a-beginner-s-guide/content/chap1/chap1.html
#   COMPREHENSIVE: https://cgold.readthedocs.io/en/latest/index.html
#   SIMPLE: https://cmake.org/cmake-tutorial/
cmake_minimum_required(VERSION 3.10)

MESSAGE(STATUS "Processing CMakeLists.txt")

# Configure compiler
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11) # https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

project(qnp2fond CXX)   # this sets up many variables: https://cgold.readthedocs.io/en/latest/tutorials/project.html
set(PROJECT_VERSION "1.0.0")

# Set a few variables on where to put different binaries/libraries
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# REPORT the value of variables
MESSAGE(STATUS "------- VARIABLE REPORTING ------")
foreach(X
            CMAKE_CXX_COMPILER
            CMAKE_BINARY_DIR
            CMAKE_CURRENT_BINARY_DIR
            CMAKE_SOURCE_DIR
            EXECUTABLE_OUTPUT_PATH
            LIBRARY_OUTPUT_PATH)
    MESSAGE(STATUS ${X} ": " ${${X}})
endforeach()
MESSAGE(STATUS "------- VARIABLE REPORTING ------")

# equivalent to -I<dir> in gcc to look for include files - not neded if .h are in the same as sources
include_directories(src/)

set(SOURCE_FILES
        src/action.h
        src/basic.h
        src/feature.h
        src/problem.h
        src/main.cc)

add_executable(qnp2fond ${SOURCE_FILES})

