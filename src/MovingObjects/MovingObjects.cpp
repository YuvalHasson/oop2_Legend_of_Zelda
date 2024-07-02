#include "MovingObjects.h"

MovingObjects::MovingObjects(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: GameObject(texture, position, size, originOffset), m_direction(0, 0), m_speed(1), m_animation() {}

sf::Vector2f MovingObjects::getDirection()const
{
	return m_direction;
}

Animation& MovingObjects::getAnimation()
{
	return m_animation;
}

float MovingObjects::getSpeed() const
{
	return m_speed;
}

void MovingObjects::setDirection(const sf::Vector2f& direction)
{
	m_direction.x = direction.x;
	m_direction.y = direction.y;
}

void MovingObjects::move()
{	
	sf::Vector2f newPos;
	newPos.x = getSprite().getPosition().x + m_direction.x * m_speed;
	newPos.y = getSprite().getPosition().y + m_direction.y * m_speed;
	setPosition(newPos);
	getSprite().setPosition(newPos);
}

void MovingObjects::updateSprite()
{
	getSprite().setTextureRect(m_animation.getuvRect());
	getSprite().setScale(0.8f, 0.8f);
}

void MovingObjects::setGraphics(const sf::Vector2u& animationPos, int imgCount, bool singleTime, float switchTime)
{
	m_animation.setAnimation(animationPos, imgCount, singleTime, switchTime);
}

void MovingObjects::setSpeed(float speed)
{
	m_speed = speed;
}

void MovingObjects::undoMove()
{
	getSprite().setPosition(getPreviousPosition());
	setPosition(getPreviousPosition());
}
