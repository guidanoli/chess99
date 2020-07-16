#include "tests.h"
#include "test_manager.h"

void (*tests[])(void) = {
	run_print_piece_tests,
	run_board_tests,
	0,
};

int main(void)
{
	run_tests(tests);
	print_results();
	return 0;
}
