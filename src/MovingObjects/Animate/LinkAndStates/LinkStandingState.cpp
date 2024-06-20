#include <iostream>
#include "LinkStandingState.h"

std::unique_ptr<LinkState> LinkStandingState::handleInput(Input input)
{
    if(input == PRESS_SPACE)
    {
        return std::make_unique<LinkAttackState>();
    }
    else if(input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT ||
            input == PRESS_UP_RIGHT  || input == PRESS_LEFT       || input == PRESS_RIGHT   ||
            input == PRESS_DOWN      || input == PRESS_UP )
    {
        return std::make_unique<LinkMoveState>(input);
    }
    return std::make_unique<LinkStandingState>();
}

void LinkStandingState::enter(Link& link){

    if(link.isPushedBack()){
        link.move();
    }

    sf::Vector2i currentDirection = link.getDirection();

    if(currentDirection.x == 1)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkRight, 2, false , true);
    }
    else if(currentDirection.x == -1)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkLeft, 2, false , true);
    }
    else if(currentDirection == DIRECTIONS::Down)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2, false , true);
    }
    else if(currentDirection == DIRECTIONS::Up)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkUp, 2, false , true);
    }
    link.stopSwordSwipe();
    link.setPush(false);
}

