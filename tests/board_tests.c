#include "board.h"
#include "tests.h"
#include "test_manager.h"
#include "fdiff.h"

typedef struct
{
	Board* board;
	const char* expected;
}
board_test_print_case;

int board_test_print(board_test_print_case* test_case)
{
	FILE* fp1 = fopen("expected", "w+");
	FILE* fp2 = fopen("obtained", "w+");

	if (!fp1 || !fp2)
		return -1;

	fprintf(fp1, "%s", test_case->expected);
	Board_print(test_case->board, fp2);
	
	rewind(fp1);
	rewind(fp2);

	int different = fdiff(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	return different;
}

int board_test_serializing(board_test_print_case* test_case)
{
	FILE* fp1 = fopen("expected", "w+");
	FILE* fp2 = fopen("obtained", "w+");

	if (!fp1 || !fp2)
		return -1;

	fprintf(fp1, "%s", test_case->expected);
	Board_save(test_case->board, fp2);
	
	rewind(fp1);
	rewind(fp2);

	int different = fdiff(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	return different;
}

const char* expected_full_board =
"    a b c d e f g h \n"
"   _________________\n"
"8 | R N B Q K B N R |\n"
"7 | P P P P P P P P |\n"
"6 | _ _ _ _ _ _ _ _ |\n"
"5 | _ _ _ _ _ _ _ _ |\n"
"4 | _ _ _ _ _ _ _ _ |\n"
"3 | _ _ _ _ _ _ _ _ |\n"
"2 | p p p p p p p p |\n"
"1 | r n b q k b n r |\n"
"   -----------------\n";

const char* expected_serialization = 
"0 6 0\n"
"1 5 0\n"
"2 4 0\n"
"3 3 0\n"
"4 2 0\n"
"5 4 0\n"
"6 5 0\n"
"7 6 0\n"
"8 1 0\n"
"9 1 0\n"
"10 1 0\n"
"11 1 0\n"
"12 1 0\n"
"13 1 0\n"
"14 1 0\n"
"15 1 0\n"
"48 1 1\n"
"49 1 1\n"
"50 1 1\n"
"51 1 1\n"
"52 1 1\n"
"53 1 1\n"
"54 1 1\n"
"55 1 1\n"
"56 6 1\n"
"57 5 1\n"
"58 4 1\n"
"59 3 1\n"
"60 2 1\n"
"61 4 1\n"
"62 5 1\n"
"63 6 1\n"
"-1";

const char* expected_modified_board;

void run_board_tests()
{
	push_name("BoardTest");

	Board *b = Board_new();

	assert(Board_check(b));

	board_test_print_case print_test_case = {b, expected_full_board};
	assert(!board_test_print(&print_test_case));
	board_test_print_case serializing_test_case = {b, expected_serialization};
	assert(!board_test_serializing(&serializing_test_case));
	assert(Board_at(b, SQ_A1)->type_id == PTID_ROOK);
	assert(Board_at(b, SQ_A2)->type_id == PTID_PAWN);
	assert(Board_at(b, SQ_A3)->type_id == PTID_EMPTY);
	assert(Board_at(b, SQ_A1)->colour == COLOUR_WHITE);
	assert(Board_at(b, SQ_A8)->colour == COLOUR_BLACK);

	Board_delete(b);

	pop_name();
}
