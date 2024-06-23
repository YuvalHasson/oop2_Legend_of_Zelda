#pragma once

#include "MovingObjects.h"

class Projectiles : public MovingObjects
{
public:
	Projectiles(const sf::Texture&, const sf::Vector2f&,const sf::Vector2f&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void handleCollision() = 0;

};