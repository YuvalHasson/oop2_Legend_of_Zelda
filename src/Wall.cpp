#include "Wall.h"

Wall::Wall(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(world, texture, position)
{
}

void Wall::handleCollision(GameObject& other)
{
}
