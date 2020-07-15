add_executable(chess99test
	main.c
	fdiff.c
	print_piece_tests.c
	test_manager.c)

target_link_libraries(chess99test
	chess99lib)
