#include "LinkAttackState.h"
#include "Link.h"
#include "Utilities.h"

std::unique_ptr<LinkState> LinkAttackState::handleInput(Input input){
    return nullptr;
}

void LinkAttackState::enter(Link& link){
    // link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackUp, 3, false, false, 0.2f);
}