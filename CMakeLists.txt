cmake_minimum_required(VERSION 3.12)

project(Birb2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SYSTEM_SDL "Link Birb2D dynamically against system SDL libraries instead of
compiling them from source" OFF)
option(STATIC_SDL "Use static linking for SDL (might not work on all
systems)" OFF)

if (SYSTEM_SDL)
	add_definitions(-DSYSTEM_SDL)
else()
	if (STATIC_SDL)
		set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the library as a shared library")
	else()
		set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the library as a shared library")
	endif()

	add_subdirectory(vendor/SDL)
	include_directories(vendor/SDL/include)

	add_subdirectory(vendor/SDL_image)
	include_directories(vendor/SDL_image)

	add_subdirectory(vendor/SDL_mixer)
	include_directories(vendor/SDL_mixer/include)

	add_subdirectory(vendor/SDL_ttf)
	include_directories(vendor/SDL_ttf)
endif()

add_definitions(-DLIB_SDL)

include_directories(include/)

set(CORE_SRC
	src/audio.cpp
	src/circle.cpp
	src/color.cpp
	src/entity.cpp
	src/filesystem.cpp
	src/font.cpp
	src/graphs.cpp
	src/line.cpp
	src/logger.cpp
	src/math.cpp
	src/physics.cpp
	src/polygon.cpp
	src/random.cpp
	src/rect.cpp
	src/renderwindow.cpp
	src/scene.cpp
	src/sceneobject.cpp
	src/texture.cpp
	src/timer.cpp
	src/timestep.cpp
	src/utils.cpp
	src/values.cpp
	src/vector.cpp)

add_library(birb2d STATIC ${CORE_SRC})
target_link_libraries(birb2d
	SDL2
	SDL2main
	SDL2_image
	SDL2_ttf
	SDL2_mixer
)
target_precompile_headers(birb2d PRIVATE include/SDL.hpp)


add_executable(test
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
	src/tests/renderwindow_test.cpp
	src/tests/scene_test.cpp
	src/tests/timer_test.cpp
	src/tests/utils_test.cpp
	src/tests/values_test.cpp
	src/tests/vector_test.cpp
	#${CORE_SRC}
)


target_link_libraries(test
	birb2d
)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ./)
