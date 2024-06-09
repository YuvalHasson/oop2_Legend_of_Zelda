#pragma once

#include "GameObject.h"

class MovingObjects : public GameObject
{
public:
	MovingObjects(const sf::Texture&, const sf::Vector2f&);

	virtual void move(const sf::Time& deltaTime) = 0;
	virtual void attack(const sf::Time& deltaTime) = 0;
	virtual void handleCollision() = 0;
	virtual void updateSprite(const sf::IntRect&);

protected:
	bool m_attacking;

private:
	int m_speed;
	int m_hp;

};