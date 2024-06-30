#include "Hole.h"

bool Hole::m_registerit = Factory<StaticObjects>::instance()->registerit("Hole",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Hole>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Hole::Hole(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position, sf::Vector2f(tileSize, tileSize), sf::Vector2f(0, 0))
{
	getSprite().setColor(sf::Color::Transparent);
}
