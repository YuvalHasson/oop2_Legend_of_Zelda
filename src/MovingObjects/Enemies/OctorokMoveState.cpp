#include "OctorokMoveState.h"
#include "OctorokStandingState.h"
#include "Octorok.h"

OctorokMoveState::OctorokMoveState(Input direction) : m_direction(direction) {}

std::unique_ptr<OctorokState> OctorokMoveState::handleInput(Input input)
{
	if (input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT ||
		input == PRESS_UP_RIGHT || input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
		input == PRESS_UP){
			return std::make_unique<OctorokMoveState>(input);
	}
	return std::make_unique<OctorokMoveState>(input);
}

void OctorokMoveState::enter(Octorok& Octorok)
{
    sf::Vector2i currentDirection = Octorok.getDirection();

    if (m_direction == PRESS_RIGHT) {
        if (currentDirection != DIRECTIONS::Right) {
            Octorok.setGraphics(ANIMATIONS_POSITIONS::OctorokLeft, 2, true);
            Octorok.setDirection(DIRECTIONS::Right);
        }
    }
    else if (m_direction == PRESS_LEFT) {
        if (currentDirection != DIRECTIONS::Left) {
            Octorok.setGraphics(ANIMATIONS_POSITIONS::OctorokLeft, 2);
            Octorok.setDirection(DIRECTIONS::Left);
        }
    }
    else if (m_direction == PRESS_UP) {
        if (currentDirection != DIRECTIONS::Up) {
            Octorok.setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2, true);
            Octorok.setDirection(DIRECTIONS::Up);
        }
    }
    else if (m_direction == PRESS_DOWN) {
        if (currentDirection != DIRECTIONS::Down) {
            Octorok.setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2);
            Octorok.setDirection(DIRECTIONS::Down);
        }
    }

    Octorok.move();
}