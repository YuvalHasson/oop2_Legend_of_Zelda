#include "Projectile.h"

#include <iostream> //debugging

bool Projectile::m_registerit = Factory<Projectile>::instance()->registerit("Projectile",
    [](const sf::Vector2f& position) -> std::unique_ptr<Projectile>
    {
        return std::make_unique<Projectile>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

Projectile::Projectile(const sf::Texture& Texture, const sf::Vector2f& position)
    : Projectiles(Texture, position, sf::Vector2f(8,8), sf::Vector2f(8/2,8/2))
{
    setGraphics({ 265, 143 }, 1);
	updateSprite();
    setDirection(DIRECTIONS::Down);
}

void Projectile::update(const sf::Time& deltaTime)
{
    move();
}
