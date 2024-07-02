#include "Wall.h"

bool Wall::m_registerit = Factory<StaticObjects>::instance()->registerit("Wall",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Wall>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position, sf::Vector2f(tileSize, tileSize), sf::Vector2f(0.f, 0.f))
{
	getSprite().setColor(sf::Color::Transparent);
}
