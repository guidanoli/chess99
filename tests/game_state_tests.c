#include "tests.h"
#include "test_manager.h"
#include "state.h"

void run_game_state_tests()
{
	push_name("GameStateTests");

	GameState* g = GameState_new();

	assert(GameState_getTurn(g) == COLOUR_WHITE);
	assert(GameState_getPhase(g) == PHASE_RUNNING);

	GameState_delete(g);

	pop_name();
}	
