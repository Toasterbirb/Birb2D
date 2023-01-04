cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME <PROJECT_NAME>)

project(template_project
VERSION 1.0
LANGUAGES CXX)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

# Headers
include_directories(include)
include_directories(birb2d/include/)

add_subdirectory(birb2d)
include_directories(birb2d/vendor/SDL/include)

add_executable(${PROGRAM_NAME} src/main.cpp)
target_link_libraries(${PROGRAM_NAME} birb2d)
target_precompile_headers(${PROGRAM_NAME} PRIVATE birb2d/include/Birb2D.hpp)

# Copy the resources into the build directory
file(COPY ./res DESTINATION ./)
file(COPY ./birb2d/birb2d_res DESTINATION ./res/)
