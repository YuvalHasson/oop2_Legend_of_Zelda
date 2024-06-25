#include "EnemySword.h"

#include <iostream> //debugging

bool EnemySword::m_registerit = Factory<EnemySword>::instance()->registerit("EnemySword",
    [](const sf::Vector2f& position) -> std::unique_ptr<EnemySword>
    {
        return std::make_unique<EnemySword>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

EnemySword::EnemySword(const sf::Texture& Texture, const sf::Vector2f& position)
    :Weapon(Texture, position, sf::Vector2f(8, 8), sf::Vector2f(8 / 2, 8 / 2))
{
    setGraphics(ANIMATIONS_POSITIONS::EnemySwordDown, 1);
    updateSprite();
    setDirection(DIRECTIONS::Down);
    m_startTime.restart();
    m_enemyInSmartMove = false;
}

void EnemySword::update(const sf::Time&)
{
    if (m_startTime.getElapsedTime().asSeconds() > 0.4f || m_enemyInSmartMove == true)
    {
        this->getSprite().setPosition({ 0,0 });
        this->destroy();
    }
    else if (m_startTime.getElapsedTime().asSeconds() > 0.1f)
    {
        sf::Vector2f position = getSprite().getPosition();
        sf::Vector2f attackPos;
        if (this->getDirection().x == 1) {
            attackPos.x = position.x + 0.01f;
            attackPos.y = position.y;
        }
        else if (this->getDirection().x == -1) {
            attackPos.x = position.x - 0.01f;
            attackPos.y = position.y;
        }
        else if (this->getDirection() == DIRECTIONS::Up) {
            attackPos.x = position.x;
            attackPos.y = position.y - 0.01f;
        }
        else if (this->getDirection() == DIRECTIONS::Down) {
            attackPos.x = position.x;
            attackPos.y = position.y + 0.01f;
        }
        getSprite().setPosition(attackPos);
        updateSprite();
    }
}

void EnemySword::setBool()
{
    m_enemyInSmartMove = true;
}
