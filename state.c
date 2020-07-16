#include "state.h"

#include <stdlib.h>

struct GameState
{
	Board* board;
	Colour turn;
	Phase phase;
};

GameState* GameState_new()
{
	GameState* new_game_state = malloc(sizeof(GameState));
	new_game_state->board = Board_new();
	new_game_state->turn = COLOUR_WHITE;
	new_game_state->phase = PHASE_RUNNING;
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

void GameState_delete(GameState* g)
{
	Board_delete(g->board);
	free(g);
}
