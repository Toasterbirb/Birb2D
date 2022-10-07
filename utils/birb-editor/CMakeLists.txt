
cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME birb-editor)

project(template_project
VERSION 0.0.1
LANGUAGES CXX)

include_directories(include)
add_executable(${PROGRAM_NAME}
	src/main.cpp
	src/grid.cpp)
target_compile_options(${PROGRAM_NAME} PRIVATE -Wall -Wextra -Wpedantic
	-Werror)
target_link_libraries(${PROGRAM_NAME} birb2d)

# Copy the resources into the build directory
file(COPY ./res DESTINATION ./)
file(COPY ../../birb2d_res DESTINATION ./res/)
