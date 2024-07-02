#include "Pot.h"

#include <iostream> //debugging

bool Pot::m_registerit = Factory<StaticObjects>::instance()->registerit("Pot",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Pot>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});


Pot::Pot(const sf::Texture& texture, const sf::Vector2f& position)
	:Destructible(texture, position, sf::Vector2f(tileSize * 0.7f, tileSize * 0.7f), sf::Vector2f(2, 2))
{
	getSprite().setTextureRect(sf::IntRect(156, 208, tileSize, tileSize));
	getSprite().setScale(0.8f, 0.8f);
}

