#include "tests.h"
#include "test_manager.h"
#include "utils.h"
#include "types.h"

void gt08(void* arg, FILE* fp)
{
	for (int r = RK_1; r < RK_CNT; ++r)
		printRank(r, fp);
}

void gt09(void* arg, FILE* fp)
{
	for (int f = FL_A; f < FL_CNT; ++f)
		printFile(f, fp);
}

void gt10(void* arg, FILE* fp)
{
	for (int sq = SQ_A1; sq < SQ_CNT; ++sq)
		printSquare(sq, fp);
}

void gt11(void* arg, FILE* fp)
{
	for (int type_id = PTID_EMPTY; type_id < PTID_CNT; ++type_id) {
		Piece p;
		p.type_id = type_id;
		p.colour = COLOUR_WHITE;
		Piece_print(&p, fp);
	}
}

void gt12(void* arg, FILE* fp)
{
	for (int type_id = PTID_EMPTY; type_id < PTID_CNT; ++type_id) {
		Piece p;
		p.type_id = type_id;
		p.colour = COLOUR_BLACK;
		Piece_print(&p, fp);
	}
}

#define ADD_GT(n) assert(utils_gt(gt ## n, 0, #n ".dat"))

void run_type_tests()
{
	test_manager_push_name("types.h");

	test_manager_push_name("getSquareFile");

	for (int f = FL_A; f < FL_CNT; ++f) {
		for (int r = RK_1; r < RK_CNT; ++r) {
			Square sq = getSquare(f, r);
			assert(getSquareFile(sq) == f);
		}
	}

	test_manager_pop_name(); // getSquareFile

	test_manager_push_name("getSquareRank");

	for (int f = FL_A; f < FL_CNT; ++f) {
		for (int r = RK_1; r < RK_CNT; ++r) {
			Square sq = getSquare(f, r);
			assert(getSquareRank(sq) == r);
		}
	}

	test_manager_pop_name(); // getSquareRank

	test_manager_push_name("getSquare");

	for (int sq = SQ_A1; sq < SQ_CNT; ++sq) {
		File f = getSquareFile(sq);
		Rank r = getSquareRank(sq);
		assert(getSquare(f, r) == sq); 
	}

	test_manager_pop_name(); // getSquare

	test_manager_push_name("checkFile");

	for (int f = FL_A; f < FL_CNT; ++f)
		assert(checkFile(f));

	test_manager_pop_name(); // checkFile

	test_manager_push_name("checkRank");

	for (int r = RK_1; r < RK_CNT; ++r)
		assert(checkRank(r));

	test_manager_pop_name(); // checkRank

	test_manager_push_name("checkSquare");

	for (int sq = SQ_A1; sq < SQ_CNT; ++sq)
		assert(checkSquare(sq));

	test_manager_pop_name(); // checkSquare

	test_manager_push_name("checkPieceTypeId");

	for (int type_id = PTID_EMPTY; type_id < PTID_CNT; ++type_id)
		assert(checkPieceTypeId(type_id));

	test_manager_pop_name(); // checkPieceTypeId

	test_manager_push_name("checkColour");

	for (int c = COLOUR_WHITE; c < COLOUR_CNT; ++c)
		assert(checkColour(c));

	test_manager_pop_name(); // checkColour

	test_manager_push_name("checkPhase");

	for (int ph = PHASE_RUNNING; ph < PHASE_CNT; ++ph)
		assert(checkPhase(ph));

	test_manager_pop_name(); // checkPhase

	test_manager_push_name("Piece_check");

	for (int type_id = PTID_EMPTY; type_id < PTID_CNT; ++type_id) {
		for (int colour = COLOUR_WHITE; colour < COLOUR_CNT; ++colour) {
			Piece p;
			p.type_id = type_id;
			p.colour = colour;
			assert(Piece_check(&p));
		}
	}

	test_manager_pop_name(); // Piece_check

	test_manager_push_name("GT");

	ADD_GT(08);
	ADD_GT(09);
	ADD_GT(10);
	ADD_GT(11);
	ADD_GT(12);

	test_manager_pop_name(); // GT

	test_manager_pop_name(); // types.h
}
