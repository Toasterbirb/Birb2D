cmake_minimum_required(VERSION 3.12)

project(Birb2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SYSTEM_SDL "Link Birb2D dynamically against system SDL libraries instead of
compiling them from source" OFF)
option(STATIC_SDL "Use static linking for SDL (might not work on all
systems)" OFF)
option(TESTS "Compile tests" ON)
option(EXAMPLES "Compile examples" OFF)

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

# Compile tests if enabled
if (TESTS)
	add_subdirectory(tests)
endif()

# Compile examples if enabled
if (EXAMPLES)
	add_subdirectory(examples)
endif()
