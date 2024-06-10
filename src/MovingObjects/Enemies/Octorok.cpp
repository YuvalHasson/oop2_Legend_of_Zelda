#include "Octorok.h"

#include <iostream> //debug

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position), m_state(std::make_unique<OctorokStandingState>())
{
	setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2);
	updateSprite();
}


void Octorok::update(const sf::Time& deltaTime)
{ 
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    if (m_directionChangeClock.getElapsedTime().asSeconds() >= 1.0f) // Change direction every 2 seconds
    {
        int randomMovment = rand() % 4;

        std::cout << randomMovment << std::endl;

        switch (randomMovment)
        {
        case 0:
            up = true;
            break;
        case 1:
            down = true;
            break;
        case 2:
            right = true;
            break;
        case 3:
            left = true;
            break;
        default:
            break;
        }
        m_directionChangeClock.restart();
    }

    Input input;

    if (up) {
        input = PRESS_UP;
    }
    else if (down) {
        input = PRESS_DOWN;
    }
    else if (right) {
        input = PRESS_RIGHT;
    }
    else if (left) {
        input = PRESS_LEFT;
    }
    else {
        input = NONE;
    }

    std::unique_ptr<OctorokState> state = m_state->handleInput(input);

    if (state) {
        m_state = std::move(state);
        m_state->enter(*this);

        updateGraphics(deltaTime);
    }
    updateSprite();
}

void Octorok::handleCollision()
{
}

void Octorok::move()
{
    getSprite().move(sf::Vector2f(getDirection()));
}