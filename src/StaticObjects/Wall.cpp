#include "Wall.h"

#include <iostream> //debugging

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position)
{
	getSprite().setColor(sf::Color::Transparent);
	getSprite().scale(0.7f, 0.7f);
}

void Wall::handleCollision()
{

}
