#include "Zelda.h"

bool Zelda::m_registerit = Factory<Zelda>::instance()->registerit("Zelda",
	[](const sf::Vector2f& position) -> std::unique_ptr<Zelda>
	{
		return std::make_unique<Zelda>(*Resources::getResource().getTexture(TEXTURE::Zelda), position);
	});

Zelda::Zelda(const sf::Texture& texture, const sf::Vector2f& position)
	:Animate(texture, position, sf::Vector2f(7, 7.5f), sf::Vector2f(tileSize / 4.5f, tileSize / 9))
{
	getSprite().setOrigin(tileSize / 2, tileSize / 2);
	setGraphics({1, 11}, 1);
	updateSprite();
}

std::unique_ptr<Inanimate> Zelda::getAttack()
{
	return nullptr;
}