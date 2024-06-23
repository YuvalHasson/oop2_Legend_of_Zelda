#include "Projectiles.h"

Projectiles::Projectiles(const sf::Texture& Texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& offset)
	: MovingObjects(Texture, position, size, offset)
{
}