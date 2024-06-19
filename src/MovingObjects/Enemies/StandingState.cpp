#include "StandingState.h"
#include "PatrolMovement.h"
#include <iostream>

std::unique_ptr<MovementStrategy> StandingState::handleInput(Input input)
{
    if (input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT ||
        input == PRESS_UP_RIGHT || input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
        input == PRESS_UP) {
        std::cout << "StandingState\n";
        return std::make_unique<PatrolMovement>(input, nullptr);
    }
    std::cout << "StandingState\n";
    return std::make_unique<StandingState>();
}

void StandingState::enter(MovingObjects& object)
{
    object.move();
}
