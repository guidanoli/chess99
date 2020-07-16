add_executable(chess99test
	main.c
	fdiff.c
	test_manager.c
	print_piece_tests.c
	board_tests.c)

target_link_libraries(chess99test
	chess99lib)
