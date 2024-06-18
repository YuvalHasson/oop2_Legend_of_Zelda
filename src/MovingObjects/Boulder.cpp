#include "Boulder.h"

bool Boulder::m_registerit = Factory::registerit("Boulder",
	[](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<Boulder>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position); });

Boulder::Boulder(const sf::Texture& texture, const sf::Vector2f& pos)
	: MovingObjects(texture, pos, sf::Vector2f(tileSize / 1.3f, tileSize / 1.3f), sf::Vector2f(tileSize / 2.5f, tileSize / 2.5f))
{

	setPosition(pos);
	setGraphics({190, 170}, 1);
	updateSprite();
}

void Boulder::update(const sf::Time& deltaTime)
{
	setSpeed(1.f);
}

void Boulder::handleCollision()
{
}