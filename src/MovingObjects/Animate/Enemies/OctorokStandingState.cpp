#include "OctorokStandingState.h"

std::unique_ptr<OctorokState> OctorokStandingState::handleInput(Input input)
{
    if (input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
        input == PRESS_UP)
	{
            return std::make_unique<OctorokMoveState>(input);
	}
	else if (input == PRESS_SPACE)
	{
		return std::make_unique<OctorokAttackState>();
	}
    return std::unique_ptr<OctorokStandingState>();
}

void OctorokStandingState::enter(Octorok& oct) {
    if(oct.isPushedBack()){
        handleInput(PRESS_DOWN);
    }
}
