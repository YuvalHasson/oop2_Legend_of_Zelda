#include "Octorok.h"

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position)
{
	const auto& a = sf::IntRect(197, 142, tileSize, tileSize);
	updateSprite(a);
}

void Octorok::move(const sf::Time& deltaTime)
{
}

void Octorok::attack(const sf::Time& deltaTime)
{
}

void Octorok::handleCollision()
{
}
