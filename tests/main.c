#include "tests.h"
#include "utils.h"
#include "test_manager.h"

int main(void)
{
	test_manager_init();
	utils_set_gt_path(ROOT "/tests/gt/");

	run_type_tests();
	run_board_tests();
	run_game_state_tests();
	
	test_manager_print_results();
	test_manager_close();
	return 0;
}
