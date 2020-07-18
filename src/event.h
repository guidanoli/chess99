#ifndef EVENT_H
#define EVENT_H

#include "state.h"

typedef struct Event Event;
typedef int (*Event_isValid_func) (Event*, GameState const*);
typedef void (*Event_apply_func) (Event*, GameState*);

Event* Event_new(Event_isValid_func isValid,
		 Event_apply_func apply);

int Event_isValid(Event* event, GameState const* g);

void Event_apply(Event* event, GameState* g);

void Event_delete(Event* event);

#endif
