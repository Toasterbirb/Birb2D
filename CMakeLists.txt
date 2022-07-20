cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

project(Birb2D)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
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
	${CORE_SRC}
)

target_link_libraries(test
	SDL2::Main
	SDL2::Image
	SDL2::GFX
	SDL2::TTF
	SDL2::Mixer
)

add_library(birb2d
	${CORE_SRC})

target_link_libraries(birb2d
	SDL2::Main
	SDL2::Image
	SDL2::GFX
	SDL2::TTF
	SDL2::Mixer
)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ./)
