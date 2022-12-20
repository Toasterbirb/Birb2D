cmake_minimum_required(VERSION 3.12)

project(Birb2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

option(SYSTEM_SDL "Link Birb2D dynamically against system SDL libraries instead of
compiling them from source" OFF)
option(STATIC_SDL "Use static linking for SDL" ON)
option(TESTS "Compile tests" ON)
option(UTILS "Compile extra utilities" ON)
option(EXAMPLES "Compile examples" OFF)
option(DEBUG "Enable some extra debug output" ON)
option(RELEASE "Compile a release build" OFF)
option(JOYSTICK "Enable joystick support." OFF)
option(WINDOWS_BUILD "Enable some windows specific options" OFF)
option(PROFILER "Enable the profiler timers" OFF)
option(BUNDLED_ASSETS "Bundle game assets directly into the game binary" OFF)

if (BUNDLED_ASSETS)
	add_definitions(-DBUNDLED_ASSETS)
endif()

if (DEBUG)
	add_definitions(-DDEBUG)
endif()

if (RELEASE)
	set(CMAKE_BUILD_TYPE Release)
	set(STATIC_SDL ON)
else()
	set(CMAKE_BUILD_TYPE Debug)

	# Disable debug postfixes
	set(DISABLE_FORCE_DEBUG_POSTFIX ON CACHE BOOL "Disable forced debug
	postfixes")
	set(SDL_CMAKE_DEBUG_POSTFIX "" CACHE STRING "Name suffix for debug builds")
	set(SDL2IMAGE_DEBUG_POSTFIX "" CACHE STRING "Name suffix for debug builds")
	set(SDL2MIXER_DEBUG_POSTFIX "" CACHE STRING "Name suffix for debug builds")
	set(SDL2TTF_DEBUG_POSTFIX "" CACHE STRING "Name suffix for debug builds")
endif()

if (NOT JOYSTICK)
	set(SDL_JOYSTICK OFF CACHE BOOL "Disable joystick support")
	set(SDL_HAPTIC OFF CACHE BOOL "Disable haptic support")
endif()

if (WINDOWS_BUILD)
	#add_definitions(-DWINDOWS)
	set(UTILS OFF)
endif()

if (PROFILER)
	# Enable microprofiler
	add_compile_definitions(MICROPROFILE_ENABLED=1)
else()
	# Disable microprofiler
	add_compile_definitions(MICROPROFILE_ENABLED=0)
endif()

if (STATIC_SDL)
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the library as a shared library")
endif()

# Include the microprofiler. It should get disabled by the
# MICROPROFILER_ENABLED variable if it is set to zero
add_subdirectory(vendor/microprofile)

# Include libzip and cppcodec
find_package(ZLIB)

if (${ZLIB_FOUND})
	set(ZLIB_USE_STATIC_LIBS "ON")
	option(ENABLE_COMMONCRYPTO "Enable use of CommonCrypto" OFF)
	option(ENABLE_GNUTLS "Enable use of GnuTLS" OFF)
	option(ENABLE_MBEDTLS "Enable use of mbed TLS" OFF)
	option(ENABLE_OPENSSL "Enable use of OpenSSL" OFF)
	option(ENABLE_WINDOWS_CRYPTO "Enable use of Windows cryptography libraries" OFF)
	option(ENABLE_BZIP2 "Enable use of BZip2" OFF)
	option(ENABLE_LZMA "Enable use of LZMA" OFF)
	option(ENABLE_ZSTD "Enable use of Zstandard" OFF)
	option(BUILD_TOOLS "Build tools in the src directory (zipcmp, zipmerge,
	ziptool)" OFF)
	option(BUILD_REGRESS "Build regression tests" OFF)
	option(BUILD_EXAMPLES "Build examples" OFF)
	option(BUILD_DOC "Build documentation" OFF)
	option(LIBZIP_DO_INSTALL "Install libzip and the related files" OFF)
	option(SHARED_LIB_VERSIONNING "Add SO version in .so build" OFF)
	add_subdirectory(vendor/libzip)
	add_subdirectory(vendor/cppcodec)
	include_directories(vendor/cppcodec)
endif()

if (SYSTEM_SDL)
	add_definitions(-DSYSTEM_SDL)
else()
	if (STATIC_SDL)
		set(BUILD_STATIC ON CACHE BOOL "Build static libs")

		set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored third-party libraries")
		set(SDL2MIXER_VENDORED ON CACHE BOOL "Use vendored third-party libraries")
		set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored third-party libraries")

		add_definitions(-DSTATIC_SDL)
	else()
		set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the library as a shared library")
	endif()

	# Disable some unnecessary SDL stuff
	set(SDL2_DISABLE_SDL2MAIN OFF CACHE BOOL "Disable building/installation of
	SDL2main")
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
	add_subdirectory(vendor/SDL_mixer)
	add_subdirectory(vendor/SDL_ttf)
	add_subdirectory(vendor/SDL2_gfx)
endif()

include_directories(include/)

set(CORE_SRC
	src/appinfo.cpp
	src/assetmanager.cpp
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
	src/render.cpp
	src/renderwindow.cpp
	src/resources.cpp
	src/scene.cpp
	src/sceneobject.cpp
	src/splash.cpp
	src/stopwatch.cpp
	src/texture.cpp
	src/timer.cpp
	src/timestep.cpp
	src/utils.cpp
	src/ui.cpp

	src/Vector/vector3.cpp
	src/Vector/vector3int.cpp
	src/Vector/vector2.cpp
	src/Vector/vector2int.cpp

	src/EntityComponent/animation.cpp
	src/EntityComponent/click.cpp
	src/EntityComponent/progressbar.cpp
	src/EntityComponent/text.cpp
)

add_library(birb2d STATIC ${CORE_SRC})
target_include_directories(birb2d PUBLIC vendor/SDL2_gfx)


if (PROFILER)
	# Compiler with less warnings when using microprofile. Microprofile
	# doesn't compile with some warnings set as errors
	target_compile_options(birb2d PRIVATE -pedantic -Wall -Wextra -Wcast-align
		-Wcast-qual -Wdisabled-optimization -Wformat=2
		-Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs
		-Wnoexcept -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Werror -Wno-unused)
else()
	target_compile_options(birb2d PRIVATE -pedantic -Wall -Wextra -Wcast-align
		-Wcast-qual -Wdisabled-optimization -Wformat=2
		-Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs
		-Wnoexcept -Wno-old-cast-style -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wundef -Werror -Wno-unused)
endif()

target_link_libraries(birb2d
	#SDL2
	SDL2main
	SDL2_image
	SDL2_ttf
	SDL2_mixer
	SDL2_gfx
	microprofile
)

if (${ZLIB_FOUND})
	target_link_libraries(birb2d zip)
endif()

target_precompile_headers(birb2d PUBLIC
	include/SDL.hpp
	include/STD.hpp)

# Compile tests if enabled
if (TESTS)
	add_subdirectory(tests)
endif()

# Compile examples if enabled
if (EXAMPLES)
	add_subdirectory(examples)
endif()

# Add utilities
if (UTILS)
	add_subdirectory(utils)
endif()
