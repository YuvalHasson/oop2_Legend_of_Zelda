#include "SwordItem.h"

bool SwordItem::m_registerit = Factory<SwordItem>::instance()->registerit("SwordItem",
	[](const sf::Vector2f& position) -> std::unique_ptr<SwordItem>
	{
		return std::make_unique<SwordItem>(*Resources::getResource().getTexture(TEXTURE::PickableItems), position);
	});

SwordItem::SwordItem(const sf::Texture& texture, const sf::Vector2f& position)
	: Pickable(texture, position, sf::Vector2f(tileSize/2 * 0.7f, 16.f* 0.7f), sf::Vector2f(16/2 * 0.7f, 16/2* 0.7f))
{

    getSprite().setTextureRect(sf::IntRect(166,1, tileSize/2, tileSize));
	getSprite().setScale(0.7f, 0.7f);
    
}
