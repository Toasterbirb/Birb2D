cmake_minimum_required(VERSION 3.12)

project(Birb2D-Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/ ${CMAKE_SOURCE_DIR}/include)

add_definitions(-DLIB_SDL)

add_executable(test
	audio_test.cpp
	circle_test.cpp
	color_test.cpp
	doctest_entry.cpp
	entity_test.cpp
	filesystem_test.cpp
	font_test.cpp
	graph_test.cpp
	input_test.cpp
	level_test.cpp
	line_test.cpp
	logger_test.cpp
	math_test.cpp
	physics_test.cpp
	polygon_test.cpp
	random_test.cpp
	rect_test.cpp
	renderwindow_test.cpp
	scene_test.cpp
	textrendering_test.cpp
	timer_test.cpp
	ui_test.cpp
	utils_test.cpp
	values_test.cpp
	vector_test.cpp
)


target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(test
	birb2d
)

file(COPY ./res DESTINATION ./)
