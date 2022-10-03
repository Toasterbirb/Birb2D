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
option(DEBUG "Enable some extra debug output" ON)

if (DEBUG)
	add_definitions(-DDEBUG)
endif()

if (SYSTEM_SDL)
	add_definitions(-DSYSTEM_SDL)
else()
	if (STATIC_SDL)
		set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the library as a shared library")
		set(BUILD_STATIC ON CACHE BOOL "Build static libs")

		set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored third-party libraries")
		set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries")
		set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries")

		add_definitions(-DSTATIC_SDL)
	else()
		set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the library as a shared library")
	endif()

	# Disable some unnecessary SDL stuff
	set(SDL2IMAGE_INSTALL OFF CACHE BOOL "Enable SDL2_image install target")
	set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "Build the SDL2_image sample program(s)")
	set(SDL2MIXER_INSTALL OFF CACHE BOOL "Enable SDL2mixer install target")
	set(SDL2MIXER_SAMPLES OFF CACHE BOOL "Build the SDL2_mixer sample program(s)")
	set(SDL2TTF_SAMPLES OFF CACHE BOOL "Build the SDL2_ttf sample program(s)")
	set(SDL2TTF_INSTALL OFF CACHE BOOL "Enable SDL2_ttf install target")

	# Toggle off some rare image formats
	set(SDL2IMAGE_LBM OFF CACHE BOOL "Support loading LBM images")
	set(SDL2IMAGE_PCX OFF CACHE BOOL "Support loading PCX images")
	set(SDL2IMAGE_PNM OFF CACHE BOOL "Support loading PNM images")
	set(SDL2IMAGE_QOI OFF CACHE BOOL "Support loading QOI images")
	set(SDL2IMAGE_XCF OFF CACHE BOOL "Support loading XCF images")
	set(SDL2IMAGE_XPM OFF CACHE BOOL "Support loading XPM images")
	set(SDL2IMAGE_XV OFF CACHE BOOL "Support loading XV images")


	add_subdirectory(vendor/SDL)
	include_directories(vendor/SDL/include)

	add_subdirectory(vendor/SDL_image)
	include_directories(vendor/SDL_image)

	add_subdirectory(vendor/SDL_mixer)
	include_directories(vendor/SDL_mixer/include)

	add_subdirectory(vendor/SDL_ttf)
	include_directories(vendor/SDL_ttf)

	add_subdirectory(vendor/SDL2_gfx)
	include_directories(vendor/SDL2_gfx)

	#include(ExternalProject)
	#ExternalProject_Add(SDL_gfx
	#	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2_gfx
	#	CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2_gfx/configure --prefix=<INSTALL_DIR>
	#	BUILD_COMMAND ${MAKE})

endif()

include_directories(include/)

set(CORE_SRC
	src/audio.cpp
	src/circle.cpp
	src/color.cpp
	src/diagnostics.cpp
	src/entity.cpp
	src/filesystem.cpp
	src/font.cpp
	src/graphs.cpp
	src/input.cpp
	src/level.cpp
	src/line.cpp
	src/logger.cpp
	src/math.cpp
	src/physics.cpp
	src/polygon.cpp
	src/random.cpp
	src/rect.cpp
	src/renderwindow.cpp
	src/resources.cpp
	src/scene.cpp
	src/sceneobject.cpp
	src/texture.cpp
	src/timer.cpp
	src/timestep.cpp
	src/utils.cpp
	src/ui.cpp
	src/values.cpp
	src/vector.cpp)

add_library(birb2d STATIC ${CORE_SRC})
target_include_directories(birb2d PUBLIC vendor/SDL2_gfx)
target_compile_options(birb2d PRIVATE -Wall -Wextra -Wpedantic -Werror)

if (STATIC_SDL)
	target_link_libraries(birb2d
		SDL2main
		SDL2_image
		SDL2_ttf
		SDL2_mixer
		SDL2_gfx
	)
else()
	target_link_libraries(birb2d
		SDL2
		SDL2main
		SDL2_image
		SDL2_ttf
		SDL2_mixer
		SDL2_gfx
	)
endif()

target_precompile_headers(birb2d PRIVATE include/SDL.hpp include/STD.hpp)

# Compile tests if enabled
if (TESTS)
	add_subdirectory(tests)
endif()

# Compile examples if enabled
if (EXAMPLES)
	add_subdirectory(examples)
endif()

# Add utilities
add_subdirectory(utils)
