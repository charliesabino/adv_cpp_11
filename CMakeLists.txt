cmake_minimum_required(VERSION 3.15...3.31)

project(
  adv_cpp_11
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE HEADERS src/*.h)

add_executable(11-1 src/11-1.cpp ${HEADERS})
add_executable(11-2 src/11-2.cpp ${HEADERS})
add_executable(11-3 src/11-3.cpp ${HEADERS})
