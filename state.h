#ifndef STATE_H
#define STATE_H

#include "types.h"
#include "board.h"

typedef struct GameState GameState;

GameState* GameState_new();

Board* GameState_getBoard(GameState* g);

Colour GameState_getTurn(GameState* g);

Phase GameState_getPhase(GameState* g);

void GameState_delete(GameState* g);

#endif
