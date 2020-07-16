#ifndef STATE_H
#define STATE_H

#include <stdio.h>

#include "types.h"
#include "board.h"

// Unset EnPassant square constant
#define EN_PASSANT_NONE SQ_CNT 

typedef struct GameState GameState;

// GameState format version
extern int GameState_version;

// Create a game state
GameState* GameState_new();

// Get game board
Board* GameState_getBoard(GameState* g);

// Get current turn
Colour GameState_getTurn(GameState* g);

// Go to next turn
void GameState_nextTurn(GameState* g);

// Get current phase
Phase GameState_getPhase(GameState* g);

// Set current phase
void GameState_setPhase(GameState* g, Phase phase);

// Move piece from origin to destination
void GameState_movePiece(GameState* g, Square origin, Square dest);

// Get piece at a certain square
Piece* GameState_getPieceAt(GameState* g, Square sq);

// Clear a certain square
void GameState_clearSquare(GameState* g, Square sq);

// Get en passant square
Square GameState_getEnPassant(GameState* g);

// Set en passant square
void GameState_setEnPassant(GameState* g, Square enpassant);

// Serialize game state
void GameState_save(GameState* g, FILE* fp);

// Deserialize game state
GameState* GameState_load(FILE* fp);

// TODO:
// * Altered squares bitmap

// Delete game state
void GameState_delete(GameState* g);

// Check if game state is valid
int GameState_check(GameState* g);

// Check if en passant is valid
int checkEnPassant(Square enpassant);

#endif
