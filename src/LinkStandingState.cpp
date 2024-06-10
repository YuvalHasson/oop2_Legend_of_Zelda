#include "LinkStandingState.h"
#include "LinkAttackState.h"
#include "LinkMoveState.h"

std::unique_ptr<LinkState> LinkStandingState::handleInput(Input input){
    if(input == PRESS_SPACE){
        return std::make_unique<LinkAttackState>();
    }
    else if(input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT||
        input == PRESS_UP_RIGHT || input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
        input == PRESS_UP){
        return std::make_unique<LinkMoveState>(input);
    }
    return nullptr; //return make_unique<LinkStandingState>();
}

void LinkStandingState::enter(Link& link){
    //set graphics
}
