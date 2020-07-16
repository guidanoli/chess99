#ifndef PIECE_H
#define PIECE_H

#include "types.h"

typedef struct
{
	PieceTypeId type_id;
	Colour colour;
}
Piece;

// Print piece to file
void printPiece(Piece* p, FILE* fp);

#endif
