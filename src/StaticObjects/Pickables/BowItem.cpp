#include "BowItem.h"

bool BowItem::m_registerit = Factory<StaticObjects>::instance()->registerit("BowItem",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<BowItem>(*Resources::getResource().getTexture(TEXTURE::PickableItems), position);
	});

BowItem::BowItem(const sf::Texture& texture, const sf::Vector2f& position)
	: Pickable(texture, position, sf::Vector2f(tileSize * 0.8f / 2.f, tileSize * 0.8f), sf::Vector2f(0, 0))
{

    getSprite().setTextureRect(sf::IntRect(291,1, tileSize/2, tileSize));
	getSprite().setScale(0.8f, 0.8f);
    
}
