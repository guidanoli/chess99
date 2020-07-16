#ifndef ANSI_CHESS_TYPES_H
#define ANSI_CHESS_TYPES_H

#include <stdio.h>

// Here are defines the types used throughout the library for representing
// the most basic concepts from the chess game.

typedef enum
{
	SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
	SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
	SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
	SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
	SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
	SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
	SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
	SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
	SQ_CNT = 64
}
Square;

typedef enum
{
	RK_1, RK_2, RK_3, RK_4, RK_5, RK_6, RK_7, RK_8,
	RK_CNT = 8
}
Rank;

typedef enum
{
	FL_A, FL_B, FL_C, FL_D, FL_E, FL_F, FL_G, FL_H,
	FL_CNT = 8
}
File;

typedef enum
{
	DIR_NONE  = 0,
	DIR_NORTH = RK_CNT,
	DIR_SOUTH = -DIR_NORTH,
	DIR_EAST  = 1,
	DIR_WEST  = -DIR_EAST,
	DIR_NORTHEAST = DIR_NORTH + DIR_EAST,
	DIR_NORTHWEST = DIR_NORTH + DIR_WEST,
	DIR_SOUTHEAST = DIR_SOUTH + DIR_EAST,
	DIR_SOUTHWEST = DIR_SOUTH + DIR_WEST,
}
Direction;

typedef enum
{
	PTID_EMPTY,
	PTID_PAWN,
	PTID_KING,
	PTID_QUEEN,
	PTID_BISHOP,
	PTID_KNIGHT,
	PTID_ROOK,
	PTID_CNT = 7
}
PieceTypeId;

typedef enum
{
	COLOUR_WHITE,
	COLOUR_BLACK,
	COLOUR_CNT = 2
}
Colour;

typedef enum
{
	PHASE_RUNNING,
	PHASE_WHITE_WON,
	PHASE_BLACK_WON,
	PHASE_CNT = 3
}
Phase;

// Get square rank
Rank getSquareRank(Square sq);

// Get square file
File getSquareFile(Square sq);

// Get square in a given rank and file
Square getSquare(File f, Rank r);

// Print square to file
void printSquare(Square sq, FILE* fp);

// Print rank to file
void printRank(Rank r, FILE* fp);

// Print file to file
void printFile(File f, FILE* fp);

// Check if square is valid
int checkSquare(Square sq);

// Check if rank is valid
int checkRank(Rank r);

// Check if file is valid
int checkFile(File f);

// Check if piece type id is valid
int checkPieceTypeId(PieceTypeId ptid);

// Check if colour is valid
int checkColour(Colour c);

// Check if phase is valid
int checkPhase(Phase ph);

#endif
