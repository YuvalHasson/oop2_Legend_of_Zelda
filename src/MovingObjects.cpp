#include "MovingObjects.h"

MovingObjects::MovingObjects(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: GameObject(world, texture, position)
{
}