add_executable(tchess99
	main.c
	utils.c
	test_manager.c
	board_tests.c
	game_state_tests.c
	type_tests.c)

target_link_libraries(tchess99 chess99)
