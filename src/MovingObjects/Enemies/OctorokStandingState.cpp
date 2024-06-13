#include "OctorokStandingState.h"
#include "OctorokMoveState.h"
#include "Octorok.h"

std::unique_ptr<OctorokState> OctorokStandingState::handleInput(Input input)
{
    if (input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
        input == PRESS_UP){
            return std::make_unique<OctorokMoveState>(input);
    }
    return std::unique_ptr<OctorokStandingState>();
}

void OctorokStandingState::enter(Octorok& Octorok)
{
}
