#include "MovingObjects.h"

MovingObjects::MovingObjects(const sf::Texture& texture, const sf::Vector2f& position)
	: GameObject(texture, position), m_attacking(false)
{
}

void MovingObjects::updateSprite(const sf::IntRect& uvRect){
	getSprite().setTextureRect(uvRect);
	getSprite().setScale(1,1);
}