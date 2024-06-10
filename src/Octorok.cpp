#include "Octorok.h"

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position)
{
	const auto& a = sf::IntRect(197, 142, tileSize, tileSize);
	setGraphics({194,142}, 2);
	updateSprite();

	//const auto& a = sf::IntRect(197, 142, tileSize, tileSize);
	//updateSprite(a);
	
}


void Octorok::update(const sf::Time& deltaTime){

}

void Octorok::attack(const sf::Time& deltaTime)
{
}

void Octorok::handleCollision()
{
}
