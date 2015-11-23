project(recordio)
cmake_minimum_required(VERSION 2.8)

enable_testing()

SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_BUILD_TYPE Release)
add_definitions("-Wall -std=c++11 -static")

add_library(recordio recordio.cc)
target_link_libraries(recordio z protobuf)

add_subdirectory(test)
