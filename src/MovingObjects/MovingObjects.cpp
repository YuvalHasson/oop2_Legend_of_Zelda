#include "MovingObjects.h"
#include <iostream> //debugging

MovingObjects::MovingObjects(const sf::Texture& texture, const sf::Vector2f& position)
	: GameObject(texture, position), m_attacking(false), m_animation(), m_direction(0,0), m_speed(1)
{
		
}

void MovingObjects::updateSprite(){
	getSprite().setTextureRect(m_animation.getuvRect());
	getSprite().setScale(0.8f,0.8f);
}

sf::Vector2i MovingObjects::getDirection()const{
	return m_direction;
}

void MovingObjects::setDirection(const sf::Vector2i& direction){
	m_direction = direction;
}

void MovingObjects::move(){
	sf::Vector2f newPos;
	newPos.x = getSprite().getPosition().x + m_direction.x * m_speed;
	newPos.y = getSprite().getPosition().y + m_direction.y * m_speed;
	getSprite().setPosition(newPos);
}

void MovingObjects::setGraphics(const sf::Vector2u& animationPos, int imgCount, bool flip, bool singleTime, float switchTime){
	m_animation.setAnimation(animationPos, imgCount, flip, singleTime, switchTime);
}

void MovingObjects::updateGraphics(const sf::Time& deltaTime){
	m_animation.update(deltaTime);
}
