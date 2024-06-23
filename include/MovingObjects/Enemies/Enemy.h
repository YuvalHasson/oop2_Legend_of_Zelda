#pragma once

#include "MovingObjects.h"

class Enemy : public MovingObjects
{
public:
	Enemy(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&,const sf::Vector2f&);

	virtual void handleCollision() = 0;

	virtual std::unique_ptr<MovingObjects> getAttack() = 0;
	virtual sf::Vector2f getLinkPos() = 0;
private:

};