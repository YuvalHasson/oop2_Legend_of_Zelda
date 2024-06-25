#include "Heart.h"

bool Heart::m_registerit = Factory<StaticObjects>::instance()->registerit("Heart",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Heart>(*Resources::getResource().getTexture(TEXTURE::PickableItems), position);
	});

Heart::Heart(const sf::Texture& texture, const sf::Vector2f& position)
	: Pickable(texture, position, sf::Vector2f(5.f, 5.f), sf::Vector2f(16 / 2 * 0.7f, 16 / 2 * 0.7f))
{
	getSprite().setTextureRect(sf::IntRect(166.f, 31.f, 7.f, 7.f));
	getSprite().setScale(0.7f, 0.7f);
}