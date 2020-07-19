#ifndef EVENT_H
#define EVENT_H

#include "state.h"
#include "types.h"

// IEvent interface

typedef struct IEvent IEvent;

int Event_isValid(IEvent const* event, GameState const* g);

void Event_apply(IEvent const* event, GameState* g);

// Move implementation of IEvent

typedef struct Move Move;

Move* Move_new(Square origin, Square dest);

Square Move_getOrigin(Move const* move);

Square Move_getDestination(Move const* move);

void Move_delete(Move* move);

#endif
