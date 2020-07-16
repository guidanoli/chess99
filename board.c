#include "board.h"

#include <stdlib.h>

struct Board
{
	Piece* data;
};

static PieceTypeId first_rank_ids[] = {
	PTID_ROOK,
	PTID_KNIGHT,
	PTID_BISHOP,
	PTID_QUEEN,
	PTID_KING,
	PTID_BISHOP,
	PTID_KNIGHT,
	PTID_ROOK
};

#define R_MIRROR(b, r, f, t) \
do { \
	Piece* white = Board_at(b, getSquare(r, f)); \
	Piece* black = Board_at(b, getSquare(RK_8 - r, f)); \
	white->type_id = black->type_id = t; \
	white->colour = COLOUR_WHITE; \
	black->colour = COLOUR_BLACK; \
} while(0)

Board* Board_new()
{
	Board* new_board = malloc(sizeof(Board));
	new_board->data = malloc(sizeof(Piece)*SQ_CNT);

	// First rank
	for (int f = FL_A; f < FL_CNT; ++f)
		R_MIRROR(new_board, RK_1, f, first_rank_ids[f]);

	// Second rank
	for (int f = FL_A; f < FL_CNT; ++f)
		R_MIRROR(new_board, RK_2, f, PTID_PAWN);
	
	// Middle ranks
	for (int sq = SQ_A3; sq <= SQ_H6; ++sq)
		Board_at(new_board, sq)->type_id = PTID_EMPTY;
	
	return new_board;
}

Piece* Board_at(Board* board, Square sq)
{
	return board->data + sq;
}

void Board_print(Board* board, FILE* fp)
{
	fprintf(fp, "    ");
	for (char fc = 'a'; fc <= 'h'; ++fc)
		fprintf(fp, "%c ", fc);
	fprintf(fp, "\n   _");
	for (char fc = 'a'; fc <= 'h'; ++fc)
		fprintf(fp, "__");
	fprintf(fp, "\n");
	for (int r = RK_8; r >= RK_1; --r) {
		fprintf(fp, "%d | ", r - RK_1 + 1);
		for (int f = FL_A; f <= FL_H; ++f) {
			Square sq = getSquare(r, f);
			printPiece(Board_at(board, sq), fp);
			fprintf(fp, " ");
		}
		fprintf(fp, "|\n");
	}
	fprintf(fp, "   ");
	for (char fc = 'a'; fc <= 'h'; ++fc)
		fprintf(fp, "--");
	fprintf(fp, "-\n");
}

void Board_delete(Board* board)
{
	free(board->data);
	free(board);
}
