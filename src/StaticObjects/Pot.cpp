#include "Pot.h"

#include <iostream> //debugging

bool Pot::m_registerit = Factory<StaticObjects>::instance()->registerit("Pot",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Pot>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});


Pot::Pot(const sf::Texture& texture, const sf::Vector2f& position)
	:Destructible(texture, position, sf::Vector2f(tileSize / 2.f, tileSize / 2.f), sf::Vector2f(tileSize / 3.8f, tileSize / 3.8f))
{
	setPosition(position);
	getSprite().setTextureRect(sf::IntRect(156, 207, tileSize, tileSize));
	getSprite().setScale(0.6, 0.6);
}

void Pot::handleCollision() {}