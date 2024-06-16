#include "Pot.h"

#include <iostream> //debugging

bool Pot::m_registerit = Factory::registerit("Pot",
	[](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<Pot>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position); });

Pot::Pot(const sf::Texture& texture, const sf::Vector2f& position)
	:Destructible(texture, position, sf::Vector2f(14,14), sf::Vector2f(tileSize/2, tileSize/2))
{
	getSprite().setTextureRect(sf::IntRect(156, 207, tileSize, tileSize));
	getSprite().setScale(1, 1);
}

void Pot::handleCollision()
{
	destroy();
	std::cout << "Pot collision\n";
}
