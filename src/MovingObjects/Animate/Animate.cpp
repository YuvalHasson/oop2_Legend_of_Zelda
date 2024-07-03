#include "Animate.h"

Animate::Animate(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: MovingObjects(texture, position, size, originOffset), m_attacking(false), 
	  m_hp(1), m_isPushedback(false), m_hitAnimation(getSprite().getColor()) {}

void Animate::updateHitAnimation(const sf::Time& deltaTime){
	m_hitAnimation.update(deltaTime);
}

void Animate::move()
{
	sf::Vector2f newPos;
	if (m_isPushedback)
	{
		if (!(pushbackDuration - m_pushbackTimer.getElapsedTime() <= sf::Time(sf::seconds(0))))
		{
			newPos.x = getSprite().getPosition().x + (-m_collisionDirection.x * getSpeed() * 1.5f);
			newPos.y = getSprite().getPosition().y + (-m_collisionDirection.y * getSpeed() * 1.5f);
			setPosition(newPos);
			getSprite().setPosition(newPos);
		}
		else
		{
			m_isPushedback = false;
		}
		return;
	}
	MovingObjects::move();
}

void Animate::updateGraphics(const sf::Time& deltaTime)
{
	getAnimation().update(deltaTime);
}

void Animate::setAttacking(const bool& attack)
{
	m_attacking = attack;
}

void Animate::pushBack(const sf::Vector2f& direction)
{
	m_collisionDirection = direction;
	m_isPushedback = true;
	m_pushbackTimer.restart();
}

bool Animate::isAttacking() const
{
	return m_attacking;
}

void Animate::setHp(int hp)
{
	m_hp = hp;
}

int Animate::getHp() const
{
	return m_hp;
}

bool Animate::isPushedBack() const
{
	return m_isPushedback;
}

void Animate::addHitColor(sf::Color color){
	m_hitAnimation.addColorToAnimation(color);
}

sf::Color Animate::getCurrentColor()const{
	return m_hitAnimation.getCurrentColor();
}
sf::Color Animate::getBaseColor()const{
	return m_hitAnimation.getBaseColor();
}