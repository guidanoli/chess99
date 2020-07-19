#ifndef EVENT_H
#define EVENT_H

#include "state.h"
#include "types.h"

// IEvent interface

typedef struct IEvent IEvent;
typedef int (*Event_isValid_func) (IEvent const*, GameState const*);
typedef void (*Event_apply_func) (IEvent const*, GameState*);
typedef void (*Event_delete_traits_func) (void*);

IEvent* Event_new(Event_isValid_func isValid,
		  Event_apply_func apply,
		  Event_delete_traits_func delete_traits,
		  void* traits);

int Event_isValid(IEvent const* event, GameState const* g);

void Event_apply(IEvent const* event, GameState* g);

void Event_delete(IEvent* event);

void const* Event_getTraits(IEvent const* event);

// Move implementation of IEvent

typedef struct Move Move;

IEvent* Move_new(Square origin, Square dest);

Square Move_getOrigin(Move const* move);

Square Move_getDestination(Move const* move);

#endif
