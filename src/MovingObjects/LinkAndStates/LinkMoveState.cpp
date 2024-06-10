#include <iostream>
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

    sf::Vector2i currentDirection = link.getDirection();

    if(m_direction == PRESS_RIGHT){
        if(currentDirection != DIRECTIONS::Right){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkRight, 2);
            link.setDirection(DIRECTIONS::Right);
        }
    }
    else if(m_direction == PRESS_LEFT){
        if(currentDirection != DIRECTIONS::Left){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkLeft, 2);
            link.setDirection(DIRECTIONS::Left);
        }
    }
    else if(m_direction == PRESS_UP){
        if(currentDirection != DIRECTIONS::Up){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkUp, 2);
            link.setDirection(DIRECTIONS::Up);
        }
    }
    else if(m_direction == PRESS_DOWN){
        if(currentDirection != DIRECTIONS::Down){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2);
            link.setDirection(DIRECTIONS::Down);
        }
    }
    
    link.move();
}
