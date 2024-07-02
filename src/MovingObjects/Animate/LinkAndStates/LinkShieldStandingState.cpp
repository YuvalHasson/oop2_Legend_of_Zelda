#include "LinkShieldStandingState.h"

std::unique_ptr<LinkState> LinkShieldStandingState::handleInput(Input input, bool shielding, bool pushing)
{
    if(input == PRESS_SPACE)
    {
        return std::make_unique<LinkAttackState>();
    }
    else if(input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT ||
            input == PRESS_UP_RIGHT  || input == PRESS_LEFT       || input == PRESS_RIGHT   ||
            input == PRESS_DOWN      || input == PRESS_UP )
    {
        if(!shielding && !pushing){
            return std::make_unique<LinkMoveState>(input);
        }
        else if (pushing && !shielding)
        {
			return std::make_unique<LinkPushState>(input);
        }
        else{
            return std::make_unique<LinkShieldMovingState>(input);
        }
    }
    if(!shielding){
        return std::make_unique<LinkStandingState>();
    }
    else{
        return std::make_unique<LinkShieldStandingState>();
    }
}

void LinkShieldStandingState::enter(Link& link){

    if(link.isPushedBack()){
        link.move();
    }

    sf::Vector2i currentDirection = link.getDirection();

    if(currentDirection.x == 1)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkShieldRight, 2, true);
    }
    else if(currentDirection.x == -1)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkShieldLeft, 2 , true);
    }
    else if(currentDirection == DIRECTIONS::Down)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkShieldDown, 2 , true);
    }
    else if(currentDirection == DIRECTIONS::Up)
    {
        link.setGraphics(ANIMATIONS_POSITIONS::LinkShieldUp, 2 , true);
    }
}

