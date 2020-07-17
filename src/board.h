#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

#include "types.h"

typedef struct Board Board;

// Create new board
// In case of error, returns NULL
Board* Board_new();

// Obtain piece in a given square
Piece* Board_at(Board* board, Square sq);

// Serialize board
void Board_save(Board* board, FILE* fp);

// Deserialize board
// In case of error, returns NULL
Board* Board_load(FILE *fp);

// Print board to file
void Board_print(Board* board, FILE* fp);

// Delete board
void Board_delete(Board* board);

// Check if board is valid
int Board_check(Board* board);

#endif
