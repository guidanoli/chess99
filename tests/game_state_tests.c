#include "tests.h"
#include "test_manager.h"
#include "state.h"

void run_game_state_tests()
{
	test_manager_push_name("GameStateTests");

	GameState* g = GameState_new();

	// Check initial state
	assert(GameState_check(g));
	assert(GameState_getTurn(g) == COLOUR_WHITE);
	assert(GameState_getPhase(g) == PHASE_RUNNING);
	assert(GameState_getEnPassant(g) == EN_PASSANT_NONE);

	// Switch turns	
	GameState_nextTurn(g);
	assert(GameState_getTurn(g) == COLOUR_BLACK);
	GameState_nextTurn(g);
	assert(GameState_getTurn(g) == COLOUR_WHITE);

	// Switch phase
	GameState_setPhase(g, PHASE_WHITE_WON);
	assert(GameState_getPhase(g) == PHASE_WHITE_WON);
	GameState_setPhase(g, PHASE_BLACK_WON);
	assert(GameState_getPhase(g) == PHASE_BLACK_WON);
	GameState_setPhase(g, PHASE_RUNNING);
	assert(GameState_getPhase(g) == PHASE_RUNNING);

	// Move a piece to an empty square
	GameState_movePiece(g, SQ_A2, SQ_A4);
	assert(GameState_getPieceAt(g, SQ_A2)->type_id == PTID_EMPTY);
	assert(GameState_getPieceAt(g, SQ_A4)->type_id == PTID_PAWN);
	assert(GameState_getPieceAt(g, SQ_A4)->colour == COLOUR_WHITE);

	// Move a piece to another piece
	GameState_movePiece(g, SQ_A1, SQ_A8);
	assert(GameState_getPieceAt(g, SQ_A1)->type_id == PTID_EMPTY);
	assert(GameState_getPieceAt(g, SQ_A8)->type_id == PTID_ROOK);
	assert(GameState_getPieceAt(g, SQ_A8)->colour == COLOUR_WHITE);

	// Clear an empty square
	assert(GameState_getPieceAt(g, SQ_A3)->type_id == PTID_EMPTY);
	GameState_clearSquare(g, SQ_A3);
	assert(GameState_getPieceAt(g, SQ_A3)->type_id == PTID_EMPTY);

	// Clear a square with a piece
	assert(GameState_getPieceAt(g, SQ_B1)->type_id == PTID_KNIGHT);
	assert(GameState_getPieceAt(g, SQ_B1)->colour == COLOUR_WHITE);
	GameState_clearSquare(g, SQ_B1);
	assert(GameState_getPieceAt(g, SQ_B1)->type_id == PTID_EMPTY);

	GameState_delete(g);

	test_manager_pop_name();
}	
