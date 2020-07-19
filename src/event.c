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

	// TODO: moved_piece.getType()->canApply(g, *this);
	return 0;
}

static void Move_apply(Move const* move, GameState* g)
{

}
