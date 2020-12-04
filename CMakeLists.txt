cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(FileManager VERSION 1.0)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/FileManager)
# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples)

# target_include_directories(FileManager PUBLIC ${PROJECT_BINARY_DIR})

link_libraries(FileManager)

add_executable(SearchSubject "FileManager/src/entry.cpp")
