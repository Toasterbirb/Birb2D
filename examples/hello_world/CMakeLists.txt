cmake_minimum_required(VERSION 3.12)

project(Birb2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/ birb2d/include)
add_executable(hello_world
	src/main.cpp)

target_link_libraries(hello_world
	birb2d)
