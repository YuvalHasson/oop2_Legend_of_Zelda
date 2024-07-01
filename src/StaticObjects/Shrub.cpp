#include "Shrub.h"

bool Shrub::m_registerit = Factory<StaticObjects>::instance()->registerit("Shrub",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Shrub>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Shrub::Shrub(const sf::Texture& texture, const sf::Vector2f& pos)
	: Destructible(texture, pos, sf::Vector2f(14.f, 14.f), sf::Vector2f(2.4, 2.4))
{
	getSprite().setTextureRect(sf::IntRect(103, 173, 14.f, 14.f));
	getSprite().scale(0.7f, 0.7f);
}