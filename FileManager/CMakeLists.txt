cmake_minimum_required(VERSION 3.16)

project(FileManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE SRC ${SOURCE_DIR}/*.cpp)

add_library(FileManager ${SRC})
target_include_directories(FileManager PUBLIC ${INCLUDE_DIR})

