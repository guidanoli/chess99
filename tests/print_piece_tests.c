#include "tests.h"
#include "types.h"
#include "test_manager.h"
#include "fdiff.h"

int test_print(Piece* p, const char* expected)
{
	FILE* fp1 = fopen("expected", "r+");
	FILE* fp2 = fopen("obtained", "r+");

	if (!fp1 || !fp2)
		return -1;

	printPiece(p, fp1);
	fprintf(fp2, "%s", expected);
	
	rewind(fp1);
	rewind(fp2);

	int different = fdiff(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	return different;
}

typedef struct
{
	Piece p;
	const char* expected;
}
test_print_case;

test_print_case test_print_cases[] = {
	{ { PTID_ROOK, COLOUR_BLACK }, "R"},
	{ { PTID_ROOK, COLOUR_WHITE }, "r"},
	{ { PTID_EMPTY, COLOUR_BLACK }, "_" },
	{ { PTID_EMPTY, COLOUR_WHITE }, "_" }
};

void run_print_piece_tests()
{
	push_name("PieceTest");
	size_t n = sizeof(test_print_cases)/sizeof(test_print_cases[0]);
	for (size_t i = 0; i < n; ++i) {
		Piece* p = &(test_print_cases[i].p);
		const char* expected = test_print_cases[i].expected;
		int different = test_print(p, expected);
		if (different) {
			test_failed();	
		} else {
			test_succeeded();	
		}
	}
	pop_name();
}
