#include "Projectile.h"

bool Projectile::m_registerit = Factory<Projectile>::instance()->registerit("Projectile",
    [](const sf::Vector2f& position) -> std::unique_ptr<Projectile>
    {
        return std::make_unique<Projectile>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

Projectile::Projectile(const sf::Texture& Texture, const sf::Vector2f& position)
	: Projectiles(Texture, position,
        sf::Vector2f(tileSize / 2.f * 0.6f, tileSize / 2.f * 0.6f),
        sf::Vector2f(tileSize / 4.f * 0.6f, tileSize / 4.f * 0.6f))
{
	m_timer.restart();
    setSpeed(2);
    setGraphics(SPRITE_POSITIONS::Projectile, 1);
	updateSprite();
    setDirection(DIRECTIONS::Down);
}

void Projectile::update(const sf::Time& deltaTime)
{
    move();
	if (m_timer.getElapsedTime().asSeconds() > 5)
    {
        destroy();
    }
}
