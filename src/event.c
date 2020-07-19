#include "event.h"

#include <stdlib.h>

struct IEvent
{
	Event_isValid_func isValid;
	Event_apply_func apply;
	Event_delete_traits_func delete_traits;
	void* traits;
};

IEvent* Event_new(Event_isValid_func isValid,
		  Event_apply_func apply,
		  Event_delete_traits_func delete_traits,
		  void* traits)
{
	IEvent* new_event = malloc(sizeof(IEvent));
	if (!new_event)
		return NULL;
	new_event->isValid = isValid;
	new_event->apply = apply;
	new_event->delete_traits = delete_traits;
	new_event->traits = traits;
	return new_event;
}

int Event_isValid(IEvent const* event, GameState const* g)
{
	return event->isValid(event, g);
}

void Event_apply(IEvent const* event, GameState* g)
{
	event->apply(event, g);
}

void Event_delete(IEvent* event)
{
	event->delete_traits(event->traits);
	free(event);
}

void const* Event_getTraits(IEvent const* event)
{
	return event->traits;
}

struct Move
{
	Square origin;
	Square dest;
};

int Move_isValid(IEvent const* event, GameState const* g)
{
	Move* move = (Move*) Event_getTraits(event);

	if (!checkSquare(move->origin) ||
	    !checkSquare(move->dest) ||
	    move->origin == move->dest)
		return 0;
	
	Piece* moved_piece = GameState_getPieceAt_const(g, move->origin);

	if (moved_piece->colour != GameState_getTurn(g))
		return 0;

	Piece* captured_piece = GameState_getPieceAt_const(g, move->dest);

	if (captured_piece->type_id != PTID_EMPTY &&
	    captured_piece->colour == GameState_getTurn(g))
		return 0;

	if (captured_piece->type_id == PTID_KING)
		return 0;

	// TODO: moved_piece.getType()->canApply(g, *this);
	return 0;
}

void Move_apply(IEvent const* event, GameState* g)
{

}

void Move_delete(void* traits)
{

}

IEvent* Move_new(Square origin, Square dest)
{
	Move* new_move = malloc(sizeof(Move));
	if (!new_move)
		return NULL;
	new_move->origin = origin;
	new_move->dest = dest;
	IEvent* new_event = Event_new(Move_isValid,
	                              Move_apply,
				      Move_delete,
				      new_move);
	if (!new_event) {
		free(new_move);
		return NULL;
	}
	return new_event;
}

Square Move_getOrigin(Move const* move)
{
	return move->origin;
}

Square Move_getDestination(Move const* move)
{
	return move->dest;
}
