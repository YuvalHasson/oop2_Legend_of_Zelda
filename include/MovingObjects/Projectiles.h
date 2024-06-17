#pragma once

#include "MovingObjects.h"

class Projectile : public MovingObjects
{
public:
	Projectile(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void handleCollision() = 0;

};