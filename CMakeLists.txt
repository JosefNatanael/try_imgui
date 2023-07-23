cmake_minimum_required(VERSION 3.10)

project(test_imgui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include directories
include_directories("${CMAKE_SOURCE_DIR}")


add_executable(main main.cpp)

add_subdirectory(src)

