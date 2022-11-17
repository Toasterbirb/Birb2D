cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME camera-demo)

project(CameraDemo
VERSION 1.0
LANGUAGES CXX)

add_executable(${PROGRAM_NAME}
	src/main.cpp)
target_link_libraries(${PROGRAM_NAME} birb2d)

# Copy the resources into the build directory
file(COPY ./res DESTINATION ./)
file(COPY ../../birb2d_res DESTINATION ./res/)
