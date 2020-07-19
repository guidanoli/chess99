#include "types.h"

#include <stdio.h>

Rank getSquareRank(Square sq)
{
	return sq >> 3;
}

File getSquareFile(Square sq)
{
	return sq & 7;
}

Square getSquare(File f, Rank r)
{
	return (r << 3) | f;	
}

void printSquare(Square sq, FILE* fp)
{
	printFile(getSquareFile(sq), fp);
	printRank(getSquareRank(sq), fp);
}

void printRank(Rank r, FILE* fp)
{
	putc(r - RK_1 + '1', fp);
}

void printFile(File f, FILE* fp)
{
	putc(f - FL_A + 'a', fp); 
}

int checkSquare(Square sq)
{
	return sq >= SQ_A1 && sq < SQ_CNT;
}

int checkRank(Rank r)
{
	return r >= RK_1 && r < RK_CNT;
}

int checkFile(File f)
{
	return f >= FL_A && f < FL_CNT;
}

int checkPieceTypeId(PieceTypeId ptid)
{
	return ptid >= PTID_EMPTY && ptid < PTID_CNT;
}

int checkColour(Colour c)
{
	return c == COLOUR_WHITE || c == COLOUR_BLACK;
}

int checkPhase(Phase ph)
{
	return ph >= PHASE_RUNNING && ph < PHASE_CNT;
}

void Piece_print(Piece const* p, FILE* fp)
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
		default:
			c = '?';
			goto print_char;
	}
	if (p->colour == COLOUR_BLACK)
		c += 'A' - 'a';
print_char:
	putc(c, fp);
}

int Piece_check(Piece const* p)
{
	if (!checkPieceTypeId(p->type_id))
		return 0;
	return p->type_id == PTID_EMPTY || checkColour(p->colour);
}

Direction getDirection(Square orig, Square dest)
{
	return dest - orig;
}

Square flipSquareRank(Square sq)
{
	return getSquare(getSquareFile(sq),
	                 RK_8 - getSquareRank(sq));
}

Direction getCardinalDirection(Square orig, Square dest)
{
	Rank orig_rank = getSquareRank(orig);
	File orig_file = getSquareFile(orig);

	Rank dest_rank = getSquareRank(dest);
	File dest_file = getSquareFile(dest);

	Direction dir = DIR_NONE;

	if (dest_file > orig_file)
		dir += DIR_EAST;
	else if (dest_file < orig_file)
		dir += DIR_WEST;

	if (dest_rank > orig_rank)
		dir += DIR_NORTH;
	else if (dest_rank < orig_rank)
		dir += DIR_SOUTH;

	return dir;
}
