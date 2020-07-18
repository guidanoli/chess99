add_library(chess99
	types.c
	board.c
	state.c
	event.c)
set_target_properties(chess99 PROPERTIES
	LINKER_LANGUAGE C
	C_STANDARD 99)
target_include_directories(chess99 PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}")
