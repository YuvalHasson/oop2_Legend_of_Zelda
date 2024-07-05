#include "Lock.h"

bool Lock::m_registerit = Factory<StaticObjects>::instance()->registerit("Lock",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Lock>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Lock::Lock(const sf::Texture& texture, const sf::Vector2f& pos)
	: Destructible(texture, pos, sf::Vector2f(tileSize, tileSize), sf::Vector2f(0, 0))
{
	getSprite().setTextureRect(sf::IntRect(SPRITE_POSITIONS::Lock, { tileSize, tileSize }));
}
