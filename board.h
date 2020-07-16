#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>

#include "types.h"
#include "piece.h"

typedef struct Board Board;

// Create new board
Board* Board_new();

// Obtain piece in a given square
Piece* Board_at(Board* board, Square sq);

// Print board to file
void Board_print(Board* board, FILE* fp);

// Delete board
void Board_delete(Board* board);

#endif
