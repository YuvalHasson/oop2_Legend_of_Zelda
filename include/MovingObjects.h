#pragma once

#include "GameObject.h"

class MovingObjects : public GameObject
{
public:
	MovingObjects(b2World&, const sf::Texture&, const sf::Vector2f&);

	virtual void move() = 0;
	virtual void handleCollision(GameObject&) = 0;

private:
	int m_speed;
	int m_hp;
};