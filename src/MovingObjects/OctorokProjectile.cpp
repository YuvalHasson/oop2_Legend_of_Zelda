#include "OctorokProjectile.h"

#include <iostream> //debugging

bool OctorokProjectile::m_registerit = Factory<MovingObjects>::instance()->registerit("OctorokProjectile",
	[](const sf::Vector2f& position) -> std::unique_ptr<MovingObjects>
	{
		return std::make_unique<OctorokProjectile>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
	});

OctorokProjectile::OctorokProjectile(const sf::Texture& Texture, const sf::Vector2f& position)
    : Projectile(Texture, position)
{
    setGraphics({ 265, 143 }, 1);
	updateSprite();
    setDirection(DIRECTIONS::Down);
}

void OctorokProjectile::update(const sf::Time& deltaTime)
{
    move();
}

void OctorokProjectile::handleCollision()
{
}
