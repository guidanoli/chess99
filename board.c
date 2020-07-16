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
	Piece* white = Board_at(b, getSquare(f, r)); \
	Piece* black = Board_at(b, getSquare(f, RK_8 - r)); \
	white->type_id = black->type_id = t; \
	white->colour = COLOUR_WHITE; \
	black->colour = COLOUR_BLACK; \
} while(0)

static Board* Board_new_empty()
{
	Board* new_board = malloc(sizeof(Board));

	if (!new_board)
		return NULL;

	new_board->data = malloc(sizeof(Piece)*SQ_CNT);

	if (!new_board->data) {
		free(new_board);
		return NULL;
	}

	return new_board;
}

Board* Board_new()
{
	Board* new_board = Board_new_empty();

	if (!new_board)
		return NULL;

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
			Square sq = getSquare(f, r);
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

void Board_save(Board* board, FILE* fp)
{
	for (int sq = SQ_A1; sq < SQ_CNT; ++sq) {
		Piece* p = Board_at(board, sq);
		if (p->type_id != PTID_EMPTY) {
			fprintf(fp, "%d %d %d\n",
				sq, p->type_id, p->colour);
		}
	}
	fprintf(fp, "-1");
}

Board* Board_load(FILE *fp)
{
	char buffer[BUFSIZ];
	Board* new_board = Board_new_empty();

	if (!new_board)
		return NULL;

	// Clear board
	for (int sq = SQ_A1; sq < SQ_CNT; ++sq)
		Board_at(new_board, sq)->type_id = PTID_EMPTY;
	
	int sq, type_id, colour;

	// Put non-empty pieces
	while(fgets(buffer, BUFSIZ, fp)) {
		int matches = sscanf(buffer, " %d %d %d",
		                     &sq, &type_id, &colour);
		if (matches == 3) {
			if (checkSquare(sq) &&
			    checkPieceTypeId(type_id) &&
			    checkColour(colour)) {
				Piece* p = Board_at(new_board, sq);
				p->type_id = type_id;
				p->colour = colour;
			} else {
				goto fail;
			}
		} else if (matches == 1) {
			if (!checkSquare(sq))
				return new_board;
			else
				goto fail;
		} else {
			goto fail;
		}
			
	}
fail:
	Board_delete(new_board);
	return NULL;
}

int Board_check(Board* board)
{
	for (int sq = SQ_A1; sq < SQ_CNT; ++sq)
		if (!checkPiece(Board_at(board, sq)))
			return 0;
	return 1;
}
