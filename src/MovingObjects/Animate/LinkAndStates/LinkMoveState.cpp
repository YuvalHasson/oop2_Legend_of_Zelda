#include <iostream>
#include "LinkMoveState.h"


LinkMoveState::LinkMoveState(Input direction): m_direction(direction){}

std::unique_ptr<LinkState> LinkMoveState::handleInput(Input input, bool shielding)
{
    if(input == PRESS_SPACE)
    {
        return std::make_unique<LinkAttackState>();
    }
    else if(input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT||
            input == PRESS_UP_RIGHT  || input == PRESS_LEFT       || input == PRESS_RIGHT  ||
            input == PRESS_DOWN      || input == PRESS_UP )
    {
        if(!shielding){
            return std::make_unique<LinkMoveState>(input);
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

void LinkMoveState::enter(Link& link){
    //can make directions and enums into a map
    if(link.isPushedBack()){
        link.move();
        return;
    }
    switch(m_direction){
        case PRESS_DOWN_RIGHT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkRight, 2);
            link.setDirection(DIRECTIONS::DownRight);
            break;
        case PRESS_DOWN_LEFT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkLeft, 2);
            link.setDirection(DIRECTIONS::DownLeft);
            break;
        case PRESS_UP_RIGHT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkRight, 2);
            link.setDirection(DIRECTIONS::UpRight);
            break;
        case PRESS_UP_LEFT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkLeft, 2);
            link.setDirection(DIRECTIONS::UpLeft);
            break;
        case PRESS_RIGHT:
            link.setGraphics(link.isPush() ? ANIMATIONS_POSITIONS::LinkPushRight : ANIMATIONS_POSITIONS::LinkRight, 2);
            link.setDirection(DIRECTIONS::Right);
            break;
        case PRESS_LEFT:
            link.setGraphics(link.isPush() ? ANIMATIONS_POSITIONS::LinkPushLeft : ANIMATIONS_POSITIONS::LinkLeft, 2);
            link.setDirection(DIRECTIONS::Left);
            break;
        case PRESS_DOWN:
            link.setGraphics(link.isPush() ? ANIMATIONS_POSITIONS::LinkPushDown : ANIMATIONS_POSITIONS::LinkDown, 2);
            link.setDirection(DIRECTIONS::Down);
            break;
        case PRESS_UP:
            link.setGraphics(link.isPush() ? ANIMATIONS_POSITIONS::LinkPushUp : ANIMATIONS_POSITIONS::LinkUp, 2);
            link.setDirection(DIRECTIONS::Up);
            break;
        default:
            break;
    }
    link.move();
}
