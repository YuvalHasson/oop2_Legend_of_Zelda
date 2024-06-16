#include "Octorok.h"

#include <iostream> //debug

bool Octorok::m_registerit = Factory::registerit("Octorok",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<Octorok>(*Resources::getResource().getTexture(TEXTURE::Enemies), position); });

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position, sf::Vector2f(14,14),sf::Vector2f(tileSize/2, tileSize/2)), m_state(std::make_unique<OctorokStandingState>())
{
	setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2);
	updateSprite();
    setHp(2);
}


void Octorok::update(const sf::Time& deltaTime)
{ 
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool standing = false;
    auto directionChange = m_directionChangeClock.getElapsedTime().asSeconds();
    if (directionChange >= 1.0f) // Change direction every 1 seconds
    {
        int randomMovment = rand() % 5;


        switch (randomMovment)
        {
        case 0:
            up = true;
            std::cout << "up" << std::endl;
            break;
        case 1:
            down = true;
            std::cout << "down" << std::endl;
            break;
        case 2:
            right = true;
            std::cout << "right" << std::endl;
            break;
        case 3:
            left = true;
            std::cout << "left" << std::endl;
            break;
        default:
            std::cout << "Standing" << std::endl;
            directionChange += 0.5f;
            standing = true;
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
    else if (standing)
    {
        input = STANDING;
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

    if(getHp() <= 0){
        destroy();
    }
}

void Octorok::handleCollision()
{
}

// void Octorok::move()
// {
    
//     getSprite().move(sf::Vector2f(getDirection()));
// }