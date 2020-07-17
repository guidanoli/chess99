cmake_minimum_required(VERSION 3.13.3)
project(chess99)

add_definitions(-DROOT="${CMAKE_CURRENT_LIST_DIR}")

add_library(chess99lib
	types.c
	board.c
	state.c)
set_target_properties(chess99lib PROPERTIES
	LINKER_LANGUAGE C
	C_STANDARD 99)
target_include_directories(chess99lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(tests)
