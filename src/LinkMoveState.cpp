
#include "LinkMoveState.h"
#include "LinkAttackState.h"
#include "LinkStandingState.h"
#include "Link.h"

LinkMoveState::LinkMoveState(Input direction): m_direction(direction){}

std::unique_ptr<LinkState> LinkMoveState::handleInput(Input input){
    if(input == PRESS_SPACE){
        return std::make_unique<LinkAttackState>();
    }
    else if(input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT||
        input == PRESS_UP_RIGHT || input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
        input == PRESS_UP){
        return std::make_unique<LinkMoveState>(input);
    }
    return std::make_unique<LinkStandingState>();
}

void LinkMoveState::enter(Link& link){
    //change to switch case
    //need to make it so when direction doesnt change animation doesnt reset

    if(m_direction == PRESS_RIGHT){
        link.setGraphics(ANIMATIONS_POSITIONS::LinkRight, 2);
    }
    else if(m_direction == PRESS_LEFT){
        link.setGraphics(ANIMATIONS_POSITIONS::LinkLeft, 2);
    }
    else if(m_direction == PRESS_UP){
        link.setGraphics(ANIMATIONS_POSITIONS::LinkUp, 2);
    }
    else if(m_direction == PRESS_DOWN){
        link.setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2);
    }
    
    link.move();
    link.updateSprite();
    
    
    //link.move(m_direction) check if needed to be made in the state or just set graphics 
}
