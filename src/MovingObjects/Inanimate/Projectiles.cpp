#include "Projectiles.h"

Projectiles::Projectiles(const sf::Texture& Texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& offset)
	: Weapon(Texture, position, size, offset)
{
	getSprite().setOrigin(tileSize/2, tileSize/2);
}