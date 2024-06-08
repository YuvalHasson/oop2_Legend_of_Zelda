#include "MovingObjects.h"

MovingObjects::MovingObjects(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: GameObject(world, texture, position), m_attacking(false)
{
}

void MovingObjects::updateSprite(const sf::IntRect& uvRect){
	getSprite().setTextureRect(uvRect);
	getSprite().setScale(1,1);
}