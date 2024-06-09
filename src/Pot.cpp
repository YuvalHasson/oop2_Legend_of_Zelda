#include "Pot.h"

#include <iostream> //debugging

Pot::Pot(const sf::Texture& texture, const sf::Vector2f& position)
	:Destructible(texture, position)
{
	getSprite().setTextureRect(sf::IntRect(156, 207, tileSize, tileSize));
	getSprite().setScale(1, 1);
}

void Pot::handleCollision()
{
	destroy();
	std::cout << "Pot collision\n";
}
