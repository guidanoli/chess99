#include "board.h"
#include "tests.h"
#include "test_manager.h"
#include "utils.h"

void run_board_tests()
{
	test_manager_push_name("board.h");

	Board* b = Board_new();

	test_manager_push_name("Board_check");

	assert(Board_check(b));
	
	test_manager_pop_name(); // Board_check
	
	test_manager_push_name("Board_at");

	assert(Board_at(b, SQ_A1)->type_id == PTID_ROOK);
	assert(Board_at(b, SQ_A2)->type_id == PTID_PAWN);
	assert(Board_at(b, SQ_A3)->type_id == PTID_EMPTY);
	assert(Board_at(b, SQ_A1)->colour == COLOUR_WHITE);
	assert(Board_at(b, SQ_A8)->colour == COLOUR_BLACK);
	
	test_manager_pop_name(); // Board_at
	
	test_manager_push_name("GT");

	assert(utils_gt((utils_gt_func) Board_print, b, "02.dat"));
	assert(utils_gt((utils_gt_func) Board_save, b, "03.dat"));
	
	test_manager_pop_name(); // GT

	Board_delete(b);

	test_manager_pop_name(); // Board.h
}
