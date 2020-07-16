#include "state.h"

#include <stdlib.h>
#include <string.h>

struct GameState
{
	Board* board;
	Colour turn;
	Phase phase;
	Square enpassant;
};

GameState* GameState_new()
{
	GameState* new_game_state = malloc(sizeof(GameState));
	new_game_state->board = Board_new();
	new_game_state->turn = COLOUR_WHITE;
	new_game_state->phase = PHASE_RUNNING;
	new_game_state->enpassant = EN_PASSANT_NONE;
	return new_game_state;
}

Board* GameState_getBoard(GameState* g)
{
	return g->board;
}

Colour GameState_getTurn(GameState* g)
{
	return g->turn;
}

Phase GameState_getPhase(GameState* g)
{
	return g->phase;
}

void GameState_nextTurn(GameState* g)
{
	g->turn = (g->turn == COLOUR_WHITE) ?
		COLOUR_BLACK : COLOUR_WHITE;
}

void GameState_setPhase(GameState* g, Phase phase)
{
	g->phase = phase;
}

void GameState_movePiece(GameState* g, Square origin, Square dest)
{
	Piece* origin_piece = Board_at(g->board, origin); 
	Piece* dest_piece = Board_at(g->board, dest); 

	memcpy(dest_piece, origin_piece, sizeof(Piece));
	origin_piece->type_id = PTID_EMPTY;
}

Piece* GameState_getPieceAt(GameState* g, Square sq)
{
	return Board_at(g->board, sq);
}

void GameState_clearSquare(GameState* g, Square sq)
{
	Board_at(g->board, sq)->type_id = PTID_EMPTY;
}

void GameState_delete(GameState* g)
{
	Board_delete(g->board);
	free(g);
}

Square GameState_getEnPassant(GameState* g)
{
	return g->enpassant;
}

void GameState_setEnPassant(GameState* g, Square enpassant)
{
	g->enpassant = enpassant;
}
