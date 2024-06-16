#include "Projectiles.h"

Projectile::Projectile(const sf::Texture& Texture, const sf::Vector2f& position)
	: MovingObjects(Texture, position)
{
}

void Projectile::update(const sf::Time& deltaTime)
{
}

void Projectile::handleCollision()
{
}