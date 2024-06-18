#include "Wall.h"

#include <iostream> //debugging

bool Wall::m_registerit = Factory::registerit("Wall",
	[](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<Wall>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position); });

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position, sf::Vector2f(tileSize, tileSize), sf::Vector2f(0.f, 0.f))
{
	getSprite().setColor(sf::Color::Transparent);
	getSprite().scale(0.7f, 0.7f);
}

void Wall::handleCollision() {}
