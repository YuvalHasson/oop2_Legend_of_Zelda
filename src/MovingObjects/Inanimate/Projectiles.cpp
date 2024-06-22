#include "Projectiles.h"

Projectile::Projectile(const sf::Texture& Texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& offset)
	: Inanimate(Texture, position, size, offset) {}