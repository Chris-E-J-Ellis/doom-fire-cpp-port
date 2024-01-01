cmake_minimum_required(VERSION 3.26)
project(doom_fire_cpp_port CXX)

set(CMAKE_CXX_STANDARD 20)

# add_executable(doom_dir_cpp_port src/main.cpp)

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Could just move this into the sub-folder, messing about
add_subdirectory(src)