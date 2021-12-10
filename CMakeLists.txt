cmake_minimum_required(VERSION 3.21.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

project(birb2d VERSION 0.1)

set(ENGINE_SRC
./src/font.cpp
./src/math.cpp
./src/audio.cpp
./src/scene.cpp
./src/utils.cpp
./src/entity.cpp
./src/events.cpp
./src/logger.cpp
./src/values.cpp
./src/widgets.cpp
./src/renderwindow.cpp
)

#find_package(SDL2 REQUIRED)
include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ping pong
add_executable(ping_pong ${ENGINE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/games/Ping-Pong/src/main.cpp)
target_link_libraries(ping_pong ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})

# editor
add_executable(editor ${ENGINE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/editor/src/editor.cpp)
target_link_libraries(editor ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})

# tests
add_executable(run_tests ${ENGINE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/tests.cpp)
target_link_libraries(run_tests ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
