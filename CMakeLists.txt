cmake_minimum_required(VERSION 3.12)
project(hash_map)

set(CMAKE_CXX_STANDARD 14)

add_executable(hash_map src/main.cc include/hash_map.h)
include_directories(include)
