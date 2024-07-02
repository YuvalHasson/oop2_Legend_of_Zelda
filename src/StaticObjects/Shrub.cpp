#include "Shrub.h"

bool Shrub::m_registerit = Factory<StaticObjects>::instance()->registerit("Shrub",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Shrub>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Shrub::Shrub(const sf::Texture& texture, const sf::Vector2f& pos)
	: Destructible(texture, pos, sf::Vector2f(14.f, 14.f), sf::Vector2f(2.4f, 2.4f))
{
	getSprite().setTextureRect(sf::IntRect(SPRITE_POSITIONS::Shrub, { 14, 14 }));
}