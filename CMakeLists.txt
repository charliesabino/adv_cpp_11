cmake_minimum_required(VERSION 3.15...3.31)

project(
  adv_cpp_11
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

add_executable(adv_cpp_11 ${SOURCE_FILES})
