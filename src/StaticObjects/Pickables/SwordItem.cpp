#include "SwordItem.h"

bool SwordItem::m_registerit = Factory<StaticObjects>::instance()->registerit("SwordItem",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<SwordItem>(*Resources::getResource().getTexture(TEXTURE::PickableItems), position);
	});

SwordItem::SwordItem(const sf::Texture& texture, const sf::Vector2f& position)
	: Pickable(texture, sf::Vector2f(position.x + tileSize /4.f, position.y), sf::Vector2f(tileSize * 0.8f / 2.f, tileSize * 0.8f ), sf::Vector2f(0, 0))
{

    getSprite().setTextureRect(sf::IntRect(166,1, tileSize/2, tileSize));
	getSprite().setScale(0.8f, 0.8f);
    
}
