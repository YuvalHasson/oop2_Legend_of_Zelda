#include "InDestructible.h"

InDestructible::InDestructible(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: StaticObjects(world, texture, position)
{
}