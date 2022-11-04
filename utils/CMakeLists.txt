cmake_minimum_required(VERSION 3.12)

project(Birb2D-Utils)

# Configuration tool to help with figuring out what flags were
# used when compiling Birb2D
add_executable(birb-config birb-config.cpp)
target_compile_options(birb-config PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Tool to help with creating new projects
add_executable(birb-project birb-project.cpp)
target_compile_options(birb-project PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(birb-project birb2d)

# Simple level editor for creating 2D maps
add_subdirectory(editor)

# Tool for packing assets into binary files
add_subdirectory(asset-packer)
