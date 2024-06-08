#include "Wall.h"

#include <iostream> //debugging

Wall::Wall(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(world, texture, position)
{
}

void Wall::handleCollision()
{
	std::cout << "Wall collision" << std::endl;
}
