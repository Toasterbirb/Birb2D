cmake_minimum_required(VERSION 3.12)

project(Birb2D)

option(BIRB_GLFW "Enable GLFW backend (experimental)" OFF)

if (BIRB_GLFW)
	# GLFW
	find_package(OpenGL REQUIRED)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
else()
	# SDL2
	list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_gfx REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_mixer REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
	add_definitions(-DLIB_SDL)
endif()

include_directories(include/)

set(TEST_SRC
	src/tests/audio_test.cpp
	src/tests/circle_test.cpp
	src/tests/color_test.cpp
	src/tests/doctest_entry.cpp
	src/tests/entity_test.cpp
	src/tests/filesystem_test.cpp
	src/tests/font_test.cpp
	src/tests/graph_test.cpp
	src/tests/line_test.cpp
	src/tests/logger_test.cpp
	src/tests/math_test.cpp
	src/tests/physics_test.cpp
	src/tests/polygon_test.cpp
	src/tests/random_test.cpp
	src/tests/rect_test.cpp
	src/tests/window_test.cpp
	src/tests/scene_test.cpp
	src/tests/timer_test.cpp
	src/tests/utils_test.cpp
	src/tests/values_test.cpp
	src/tests/vector_test.cpp
)

add_executable(test
	${TEST_SRC}
	src/core/audio.cpp
	src/core/circle.cpp
	src/core/color.cpp
	src/core/entity.cpp
	src/core/filesystem.cpp
	src/core/font.cpp
	src/core/graphs.cpp
	src/core/line.cpp
	src/core/logger.cpp
	src/core/math.cpp
	src/core/physics.cpp
	src/core/polygon.cpp
	src/core/random.cpp
	src/core/rect.cpp
	src/core/window.cpp
	src/core/render.cpp
	src/core/resources.cpp
	src/core/scene.cpp
	src/core/sceneobject.cpp
	src/core/texture.cpp
	src/core/timer.cpp
	src/core/timestep.cpp
	src/core/utils.cpp
	src/core/values.cpp
	src/core/vector.cpp
)

if (BIRB_GLFW)
	# GLFW
	target_link_libraries(test glfw OpenGL::GL)
else()
	# SDL2
	target_link_libraries(test
		SDL2::Main
		SDL2::Image
		SDL2::GFX
		SDL2::TTF
		SDL2::Mixer
	)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ./)
