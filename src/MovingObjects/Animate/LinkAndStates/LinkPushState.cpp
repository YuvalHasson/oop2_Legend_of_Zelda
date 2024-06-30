#include "LinkPushState.h"

LinkPushState::LinkPushState(Input direction) : m_direction(direction) {}

std::unique_ptr<LinkState> LinkPushState::handleInput(Input input, bool shielding, bool pushing)
{
    if (input == PRESS_SPACE)
    {
        return std::make_unique<LinkAttackState>();
    }
    else if (input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT  || input == PRESS_UP_LEFT   ||
            input == PRESS_UP_RIGHT   || input == PRESS_LEFT        || input == PRESS_RIGHT     ||
            input == PRESS_DOWN       || input == PRESS_UP)
    {
        if (!shielding && !pushing) {
            return std::make_unique<LinkMoveState>(input);
        }
        else if (pushing && !shielding)
        {
        	return std::make_unique<LinkPushState>(input);
        }
        else {
            return std::make_unique<LinkShieldMovingState>(input);
        }
    }
    if (!shielding) {
        return std::make_unique<LinkStandingState>();
    }
    else {
        return std::make_unique<LinkShieldStandingState>();
    }
}

void LinkPushState::enter(Link& link) {
    if (link.isPushedBack()) {
        link.move();
        return;
    }
    switch (m_direction) {
        case PRESS_RIGHT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkPushRight, 2);
            link.setDirection(DIRECTIONS::Right);
            break;
        case PRESS_LEFT:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkPushLeft, 2);
            link.setDirection(DIRECTIONS::Left);
            break;
        case PRESS_DOWN:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkPushDown, 2);
            link.setDirection(DIRECTIONS::Down);
            break;
        case PRESS_UP:
            link.setGraphics(ANIMATIONS_POSITIONS::LinkPushUp, 2);
            link.setDirection(DIRECTIONS::Up);
            break;
        default:
            break;
    }
    link.move();

}
