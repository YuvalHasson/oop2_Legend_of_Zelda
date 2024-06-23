#include "LinkArrow.h"

#include <iostream> //debugging

bool LinkArrow::m_registerit = Factory<LinkArrow>::instance()->registerit("LinkArrow",
    [](const sf::Vector2f& position) -> std::unique_ptr<LinkArrow> {
        return std::make_unique<LinkArrow>(*Resources::getResource().getTexture(TEXTURE::Link), position);
    });


//might need to add direction to constructor so arrow initializes to right direction at creation
LinkArrow::LinkArrow(const sf::Texture& Texture, const sf::Vector2f& position)
    : Projectiles(Texture, position, sf::Vector2f(8,8), sf::Vector2f(8/2,8/2))
{
}

void LinkArrow::update(const sf::Time& deltaTime)
{
    move();
}

void LinkArrow::handleCollision()
{
}

void LinkArrow::initArrow(const sf::Vector2i& direction){
    setSpeed(2);
    sf::Vector2i arrowDirection;
    if(direction == DIRECTIONS::Down){
        setGraphics(ANIMATIONS_POSITIONS::ArrowDown, 1);
        arrowDirection = direction;
    }
    else if( direction == DIRECTIONS::Up){
        setGraphics(ANIMATIONS_POSITIONS::ArrowUp, 1);
        arrowDirection = direction;
    }
    else if(direction.x == 1){
        setGraphics(ANIMATIONS_POSITIONS::ArrowRight, 1);
        arrowDirection = DIRECTIONS::Right;
    }
    else if(direction.x == -1){
        setGraphics(ANIMATIONS_POSITIONS::ArrowLeft, 1);
        arrowDirection = DIRECTIONS::Left;
    }
    setDirection(arrowDirection);
    updateSprite();
}

