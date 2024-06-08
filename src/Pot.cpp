#include "Pot.h"

#include <iostream> //debugging

Pot::Pot(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	:Destructible(world, texture, position)
{
	getSprite().setTextureRect(sf::IntRect(156, 207, tileSize, tileSize));
	getSprite().scale(tileSize, tileSize);
}

void Pot::handleCollision()
{
	destroy();
	std::cout << "Pot collision\n";
}
