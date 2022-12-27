cmake_minimum_required(VERSION 3.12)

project(Memory-Leak-Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/ ${CMAKE_SOURCE_DIR}/include)

add_definitions(-DLIB_SDL)

set(WARNINGS -Wall -Wextra -Wpedantic -Werror)

file(COPY ../res DESTINATION ./)
file(COPY ../../birb2d_res DESTINATION ./res/)

function (add_test_target TEST_NAME)
	add_executable(${TEST_NAME}
		${TEST_NAME}.cpp)

	target_compile_options(${TEST_NAME} PRIVATE ${WARNINGS})
	target_link_libraries(${TEST_NAME}
		birb2d
	)
endfunction()

add_test_target(empty_window)
add_test_target(loaded_font)
add_test_target(unloaded_font)
add_test_target(load_nonexistant_font)
