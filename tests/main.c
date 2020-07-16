#include "tests.h"
#include "test_manager.h"

void (*tests[])() = {
	run_type_tests,
	run_print_piece_tests,
	run_board_tests,
	run_game_state_tests,
	0,
};

int main(void)
{
	run_tests(tests);
	print_results();
	return 0;
}
