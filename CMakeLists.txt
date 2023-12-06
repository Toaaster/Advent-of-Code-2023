cmake_minimum_required(VERSION 3.26)
project(aoc2023 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMKAE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)

# add different days
add_subdirectory("001")
add_subdirectory("002")
add_subdirectory("003")
add_subdirectory("004")
