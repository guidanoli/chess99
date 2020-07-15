#include "types.h"

#include <stdio.h>

Rank getSquareRank(Square sq)
{
	return (Rank) (((int) sq) >> 3);
}

File getSquareFile(Square sq)
{
	return (File) ((int) sq & 7);
}

Square getSquare(Rank r, File f)
{
	return (Square) ((((int) r) << 3) | ((int) f));	
}

void printSquare(Square sq, FILE* fp)
{
	printFile(getSquareFile(sq), fp);
	printRank(getSquareRank(sq), fp);
}

void printRank(Rank r, FILE* fp)
{
	putc(((int) r - (int) RK_1) + '1', fp);
}

void printFile(File f, FILE* fp)
{
	putc(((int) f - (int) FL_A) + 'a', fp); 
}

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
