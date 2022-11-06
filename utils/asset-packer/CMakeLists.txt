cmake_minimum_required(VERSION 3.12)

project(Birb2D-Asset-Packer)
set(APPLICATION "birb-asset-packer")

include_directories(include)

add_executable(${APPLICATION} src/main.cpp)
target_compile_options(${APPLICATION} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(${APPLICATION} birb2d)
