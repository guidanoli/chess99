#include "state.h"

#include <stdlib.h>
#include <string.h>

int GameState_version = 0;

struct GameState
{
	Board* board;
	Colour turn;
	Phase phase;
	Square enpassant;
};

static GameState* GameState_new_empty()
{
	return malloc(sizeof(GameState));
}

GameState* GameState_new()
{
	GameState* new_game_state = GameState_new_empty();
	if (!new_game_state)
		return NULL;
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

Board const* GameState_getBoard_const(GameState const* g)
{
	return g->board;
}

Colour GameState_getTurn(GameState const* g)
{
	return g->turn;
}

Phase GameState_getPhase(GameState const* g)
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

Piece const* GameState_getPieceAt_const(GameState const* g, Square sq)
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

Square GameState_getEnPassant(GameState const* g)
{
	return g->enpassant;
}

void GameState_setEnPassant(GameState* g, Square enpassant)
{
	g->enpassant = enpassant;
}

void GameState_save(GameState const* g, FILE* fp)
{
	fprintf(fp, "%d\n", GameState_version);
	fprintf(fp, "%d %d %d\n", g->turn, g->phase, g->enpassant);
	Board_save(g->board, fp);
}

GameState* GameState_load(FILE* fp)
{
	char buffer[BUFSIZ];
	GameState* new_game_state = GameState_new_empty();
	if (!new_game_state)
		return NULL;
	if (fgets(buffer, BUFSIZ, fp)) {
		int version;
		int matches = sscanf(buffer, " %d", &version);
		if (matches == 1) {
			if (version != GameState_version)
				goto fail;
		}
	} else {
		goto fail;
	}
	if (fgets(buffer, BUFSIZ, fp)) {
		int turn, phase, enpassant;
		int matches = sscanf(buffer, " %d %d %d",
		                     &turn, &phase, &enpassant);
		if (matches == 3) {
			new_game_state->turn = turn;
			new_game_state->phase = phase;
			new_game_state->enpassant = enpassant;
		} else {
			goto fail;
		}
	} else {
		goto fail;
	}
	if (!(new_game_state->board = Board_load(fp)))
		goto fail;
	return new_game_state;
fail:
	free(new_game_state);
	return NULL;
}

int GameState_check(GameState const* g)
{
	return Board_check(g->board) &&
	       checkColour(g->turn) &&
               checkPhase(g->phase) &&
	       checkEnPassant(g->enpassant);	       
}

int checkEnPassant(Square enpassant)
{
	if (enpassant == EN_PASSANT_NONE)
		return 1;
	if (!checkSquare(enpassant))
		return 0;
	Rank r = getSquareRank(enpassant);
	return r == RK_3 || r == RK_6;
}
