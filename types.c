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

Square getSquare(Rank r, File f)
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

