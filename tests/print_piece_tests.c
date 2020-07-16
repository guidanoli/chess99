#include "tests.h"
#include "test_manager.h"
#include "fdiff.h"
#include "types.h"

typedef struct
{
	Piece p;
	const char* expected;
}
piece_test_print_case;

int piece_test_print(piece_test_print_case* test_case)
{
	FILE* fp1 = fopen("expected", "w+");
	FILE* fp2 = fopen("obtained", "w+");

	if (!fp1 || !fp2)
		return -1;

	fprintf(fp1, "%s", test_case->expected);
	printPiece(&(test_case->p), fp2);
	
	rewind(fp1);
	rewind(fp2);

	int different = fdiff(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	return different;
}

piece_test_print_case piece_test_print_cases[] = {
	{ { PTID_ROOK, COLOUR_BLACK }, "R"},
	{ { PTID_ROOK, COLOUR_WHITE }, "r"},
	{ { PTID_EMPTY, COLOUR_BLACK }, "_" },
	{ { PTID_EMPTY, COLOUR_WHITE }, "_" }
};

void run_print_piece_tests()
{
	push_name("PieceTest");
	size_t n = sizeof(piece_test_print_cases)/sizeof(piece_test_print_cases[0]);
	for (size_t i = 0; i < n; ++i)
		assert(!piece_test_print(&(piece_test_print_cases[i])));

	pop_name();
}
