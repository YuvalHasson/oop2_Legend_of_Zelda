#include "Boulder.h"

bool Boulder::m_registerit = Factory::registerit("Boulder",
	[](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<Boulder>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position); });

Boulder::Boulder(const sf::Texture& texture, const sf::Vector2f& pos)
	: MovingObjects(texture, pos, sf::Vector2f(16, 16), sf::Vector2f(tileSize / 2, tileSize / 2))
{
	setGraphics({190, 170}, 1);
	updateSprite();
}

void Boulder::update(const sf::Time& deltaTime)
{
}

void Boulder::handleCollision()
{
}