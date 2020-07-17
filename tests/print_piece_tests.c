#include "tests.h"
#include "test_manager.h"
#include "fdiff.h"
#include "types.h"

typedef struct
{
	Piece p;
	const char* gt;
}
piece_tc;

piece_tc cases[] = {
	{ { PTID_ROOK, COLOUR_BLACK }, "04.dat" },
	{ { PTID_ROOK, COLOUR_WHITE }, "05.dat" },
	{ { PTID_EMPTY, COLOUR_BLACK }, "06.dat" },
	{ { PTID_EMPTY, COLOUR_WHITE }, "07.dat" }
};

void run_print_piece_tests()
{
	push_name("PieceTest");

      	size_t n = sizeof(cases)/sizeof(cases[0]);
	for (size_t i = 0; i < n; ++i) {
		Piece *p = &(cases[i].p);
		assert(Piece_check(p));
		gt_func f = (gt_func) Piece_print;
		assert(gtdiff(f, p, cases[i].gt));
	}

	pop_name();
}
