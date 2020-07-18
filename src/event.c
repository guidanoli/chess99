#include "event.h"

#include <stdlib.h>

struct Event
{
	Event_isValid_func isValid;
	Event_apply_func apply;
};

Event* Event_new(Event_isValid_func isValid,
		 Event_apply_func apply)
{
	Event* new_event = malloc(sizeof(Event));
	if (!new_event)
		return NULL;
	new_event->isValid = isValid;
	new_event->apply = apply;
	return new_event;
}

int Event_isValid(Event* event, GameState const* g)
{
	return event->isValid(event, g);
}

void Event_apply(Event* event, GameState* g)
{
	event->apply(event, g);
}

void Event_delete(Event* event)
{
	free(event);
}
