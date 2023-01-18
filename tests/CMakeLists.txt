cmake_minimum_required(VERSION 3.12)

project(Birb2D-Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/ ${CMAKE_SOURCE_DIR}/include)

add_definitions(-DLIB_SDL)

add_executable(test
	doctest_entry.cpp
	general_tests/assetmanager_test.cpp
	general_tests/audio_test.cpp
	general_tests/circle_test.cpp
	general_tests/color_test.cpp
	general_tests/diagnostics_test.cpp
	general_tests/entity_test.cpp
	general_tests/error_fuse_test.cpp
	general_tests/filesystem_test.cpp
	general_tests/font_test.cpp
	general_tests/game_test.cpp
	general_tests/graph_test.cpp
	general_tests/input_test.cpp
	general_tests/keep_tests.cpp
	general_tests/legacy_render_test.cpp
	general_tests/level_test.cpp
	general_tests/line_test.cpp
	general_tests/logger_test.cpp
	general_tests/math_test.cpp
	general_tests/particle_test.cpp
	general_tests/physics_test.cpp
	general_tests/polygon_test.cpp
	general_tests/random_test.cpp
	general_tests/rect_test.cpp
	general_tests/renderwindow_test.cpp
	general_tests/scene_test.cpp
	general_tests/splash_test.cpp
	general_tests/texture_test.cpp
	general_tests/timer_test.cpp
	general_tests/utils_test.cpp
	general_tests/values_test.cpp
	general_tests/var_test.cpp
	general_tests/vector_test.cpp

	general_tests/entities/text_test.cpp
	general_tests/entities/image_test.cpp
)

target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(test
	birb2d
)

# Input tests that require user action
add_executable(input_test
	doctest_entry.cpp
	ui_tests/button_test.cpp
	ui_tests/main_menu_test.cpp)

target_compile_options(input_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(input_test
	birb2d
)

# Compartmentalized tests for finding memory leaks
add_subdirectory(mem_leak_tests)

file(COPY ./res DESTINATION ./)
file(COPY ../birb2d_res DESTINATION ./res/)
