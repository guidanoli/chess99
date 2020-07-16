#include "piece.h"

void printPiece(Piece* p, FILE* fp)
{
	char c;
	switch (p->type_id)
	{
		case PTID_EMPTY:
			c = '_';
			goto print_char;
		case PTID_PAWN:
			c = 'p';
			break;
		case PTID_KING:
			c = 'k';
			break;
		case PTID_QUEEN:
			c = 'q';
			break;
		case PTID_BISHOP:
			c = 'b';
			break;
		case PTID_KNIGHT:
			c = 'n';
			break;
		case PTID_ROOK:
			c = 'r';
			break;
	}
	if (p->colour == COLOUR_BLACK)
		c += 'A' - 'a';
print_char:
	putc(c, fp);
}

int checkPiece(Piece* p)
{
	return checkPieceTypeId(p->type_id) &&
	       checkColour(p->colour);
}
