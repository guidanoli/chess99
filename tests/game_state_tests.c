#include "utils.h"
#include "tests.h"
#include "test_manager.h"
#include "state.h"

void run_game_state_tests()
{
	test_manager_push_name("state.h");

	GameState* g = GameState_new();

	test_manager_push_name("InitialState");

	assert(GameState_check(g));
	assert(GameState_getTurn(g) == COLOUR_WHITE);
	assert(GameState_getPhase(g) == PHASE_RUNNING);
	assert(GameState_getEnPassant(g) == EN_PASSANT_NONE);

	test_manager_pop_name(); // InitialState

	test_manager_push_name("GT");

	assert(utils_gt((utils_gt_func) GameState_save, g, "01.dat"));

	test_manager_pop_name(); // GT

	test_manager_push_name("Turn");

	GameState_nextTurn(g);
	assert(GameState_getTurn(g) == COLOUR_BLACK);
	GameState_nextTurn(g);
	assert(GameState_getTurn(g) == COLOUR_WHITE);

	test_manager_pop_name(); // Turn

	test_manager_push_name("Phase");

	GameState_setPhase(g, PHASE_WHITE_WON);
	assert(GameState_getPhase(g) == PHASE_WHITE_WON);
	GameState_setPhase(g, PHASE_BLACK_WON);
	assert(GameState_getPhase(g) == PHASE_BLACK_WON);
	GameState_setPhase(g, PHASE_RUNNING);
	assert(GameState_getPhase(g) == PHASE_RUNNING);

	test_manager_pop_name(); // Phase

	test_manager_push_name("MoveToEmpty");

	GameState_movePiece(g, SQ_A2, SQ_A4);
	assert(GameState_getPieceAt(g, SQ_A2)->type_id == PTID_EMPTY);
	assert(GameState_getPieceAt(g, SQ_A4)->type_id == PTID_PAWN);
	assert(GameState_getPieceAt(g, SQ_A4)->colour == COLOUR_WHITE);

	test_manager_pop_name(); // MoveToEmpty

	test_manager_push_name("MoveToPiece");
	
	GameState_movePiece(g, SQ_A1, SQ_A8);
	assert(GameState_getPieceAt(g, SQ_A1)->type_id == PTID_EMPTY);
	assert(GameState_getPieceAt(g, SQ_A8)->type_id == PTID_ROOK);
	assert(GameState_getPieceAt(g, SQ_A8)->colour == COLOUR_WHITE);

	test_manager_pop_name(); // MoveToPiece

	test_manager_push_name("ClearEmpty");	

	assert(GameState_getPieceAt(g, SQ_A3)->type_id == PTID_EMPTY);
	GameState_clearSquare(g, SQ_A3);
	assert(GameState_getPieceAt(g, SQ_A3)->type_id == PTID_EMPTY);

	test_manager_pop_name(); // ClearEmpty
	
	test_manager_push_name("ClearPiece");

	assert(GameState_getPieceAt(g, SQ_B1)->type_id == PTID_KNIGHT);
	assert(GameState_getPieceAt(g, SQ_B1)->colour == COLOUR_WHITE);
	GameState_clearSquare(g, SQ_B1);
	assert(GameState_getPieceAt(g, SQ_B1)->type_id == PTID_EMPTY);

	test_manager_pop_name(); // ClearPiece

	test_manager_push_name("GT");

	assert(utils_gt((utils_gt_func) GameState_save, g, "13.dat"));

	test_manager_pop_name();

	GameState_delete(g);

	test_manager_pop_name(); // state.h
}	
