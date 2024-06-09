#include "Wall.h"

#include <iostream> //debugging

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position)
{
}

void Wall::handleCollision()
{
	std::cout << "Wall collision" << std::endl;
}
