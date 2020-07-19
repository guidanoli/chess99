#include "event.h"

#include <stdlib.h>

typedef enum
{
	EVENT_TYPE_MOVE,
}
EventType; 

struct IEvent
{
	EventType type;	
};

struct Move
{
	IEvent super;
	Square origin;
	Square dest;
};

static int Move_isValid(Move const* move, GameState const* g);
static void Move_apply(Move const* move, GameState* g);

static int Move_reachesDestination(Square orig, Square dest, Direction dir, GameState const* g);

static int PieceType_Empty_canApply(GameState const* g, Move const* move);
static int PieceType_Pawn_canApply(GameState const* g, Move const* move);
static int PieceType_King_canApply(GameState const* g, Move const* move);
static int PieceType_Queen_canApply(GameState const* g, Move const* move);
static int PieceType_Bishop_canApply(GameState const* g, Move const* move);
static int PieceType_Knight_canApply(GameState const* g, Move const* move);
static int PieceType_Rook_canApply(GameState const* g, Move const* move);

int Event_isValid(IEvent const* event, GameState const* g)
{
	switch (event->type) {
		case EVENT_TYPE_MOVE:
			return Move_isValid((Move const*) event, g);
	}
	return 0;
}

void Event_apply(IEvent const* event, GameState* g)
{
	switch (event->type) {
		case EVENT_TYPE_MOVE:
			Move_apply((Move const*) event, g);
			break;
	}
}

Move* Move_new(Square origin, Square dest)
{
	Move* new_move = malloc(sizeof(Move));
	if (!new_move)
		return NULL;
	new_move->super.type = EVENT_TYPE_MOVE;
	new_move->origin = origin;
	new_move->dest = dest;
	return new_move;
}

Square Move_getOrigin(Move const* move)
{
	return move->origin;
}

Square Move_getDestination(Move const* move)
{
	return move->dest;
}

void Move_delete(Move* move)
{
	free(move);
}

static int Move_isValid(Move const* move, GameState const* g)
{
	if (!checkSquare(move->origin) ||
	    !checkSquare(move->dest) ||
	    move->origin == move->dest)
		return 0;
	
	Piece const* moved_piece = GameState_getPieceAt_const(g, move->origin);

	if (moved_piece->colour != GameState_getTurn(g))
		return 0;

	Piece const* captured_piece = GameState_getPieceAt_const(g, move->dest);

	if (captured_piece->type_id != PTID_EMPTY &&
	    captured_piece->colour == GameState_getTurn(g))
		return 0;

	if (captured_piece->type_id == PTID_KING)
		return 0;

	return Piece_canApply(moved_piece, g, move);
}

static void Move_apply(Move const* move, GameState* g)
{

}

int Piece_canApply(Piece const* piece, GameState const* g, Move const* move)
{
	switch (piece->type_id) {
		case PTID_EMPTY:
			return PieceType_Empty_canApply(g, move);
		case PTID_PAWN:
			return PieceType_Pawn_canApply(g, move);
		case PTID_KING:
			return PieceType_King_canApply(g, move);
		case PTID_QUEEN:
			return PieceType_Queen_canApply(g, move);
		case PTID_BISHOP:
			return PieceType_Bishop_canApply(g, move);
		case PTID_KNIGHT:
			return PieceType_Knight_canApply(g, move);
		case PTID_ROOK:
			return PieceType_Rook_canApply(g, move);
		default:
			return 0;
	}
}

static int PieceType_Empty_canApply(GameState const* g, Move const* move) { return 0; }

static int PieceType_Pawn_canApply(GameState const* g, Move const* move)
{
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);
	Direction white_dir = getDirection(orig, dest);
	Square white_orig = orig;
	Piece const* origpiece = GameState_getPieceAt_const(g, orig);
	Piece const* destpiece = GameState_getPieceAt_const(g, dest);

	if (origpiece->colour == COLOUR_BLACK) {
		white_orig = flipSquareRank(white_orig);
		white_dir *= -1;
	}

	Square enpassant = GameState_getEnPassant(g);

	if (destpiece->type_id == PTID_EMPTY &&
	    enpassant != dest) {
		return (getSquareRank(white_orig) == RK_2 &&
		        white_dir == DIR_NORTH * 2) ||
			white_dir == DIR_NORTH;
	} else {
		return (white_dir == DIR_NORTHEAST ||
		        white_dir == DIR_NORTHWEST);
	}
}

static int PieceType_King_canApply(GameState const* g, Move const* move) 
{
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);

	Rank orig_rank = getSquareRank(orig);
	File orig_file = getSquareFile(orig);

	Direction dir = getDirection(orig, dest);

	return (orig_rank != RK_1 && dir == DIR_SOUTH) ||
	       (orig_rank != RK_8 && dir == DIR_NORTH) ||
	       (orig_file != FL_A && dir == DIR_WEST) ||
	       (orig_file != FL_H && dir == DIR_EAST);
}

static int PieceType_Queen_canApply(GameState const* g, Move const* move)
{
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);

	Direction dir = getCardinalDirection(orig, dest);

	return Move_reachesDestination(orig, dest, dir, g);
}

static int PieceType_Bishop_canApply(GameState const* g, Move const* move)
{
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);

	Direction dir = getCardinalDirection(orig, dest);

	if (dir != DIR_NORTHWEST &&
	    dir != DIR_SOUTHWEST &&
	    dir != DIR_NORTHEAST &&
	    dir != DIR_SOUTHEAST)
		return 0;

	return Move_reachesDestination(orig, dest, dir, g);
}

static int PieceType_Knight_canApply(GameState const* g, Move const* move)
{ 
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);

	Rank orig_rank = getSquareRank(orig);
	File orig_file = getSquareFile(orig);

	Rank dest_rank = getSquareRank(dest);
	File dest_file = getSquareFile(dest);

	int rank_diff = orig_rank - dest_rank;
	int file_diff = orig_file - dest_file;

	if (rank_diff == 0 || file_diff == 0)
		return 0;

	return rank_diff + file_diff == 3;
}

static int PieceType_Rook_canApply(GameState const* g, Move const* move)
{
	Square orig = Move_getOrigin(move);
	Square dest = Move_getDestination(move);

	Direction dir = getCardinalDirection(orig, dest);

	if (dir != DIR_NORTH &&
	    dir != DIR_SOUTH &&
	    dir != DIR_EAST &&
	    dir != DIR_WEST)
		return 0;

	return Move_reachesDestination(orig, dest, dir, g);
}

// Assumes dir != DIR_NONE
static int Move_reachesDestination(Square orig, Square dest, Direction dir, GameState const* g)
{
	while (1) {
		orig += dir;
		if (!checkSquare(orig))
			return 0;
		if (orig == dest)
			return 1;
		if (GameState_getPieceAt_const(g, orig)->type_id != PTID_EMPTY)
			return 0;
	}

}
