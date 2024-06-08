#include "Destructible.h"


Destructible::Destructible(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: StaticObjects(world, texture, position)
{
}

