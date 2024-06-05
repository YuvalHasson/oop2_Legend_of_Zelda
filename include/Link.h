#pragma once

#include "MovingObjects.h"

class Link : public MovingObjects
{
public:
	Link(b2World&, const sf::Texture&, const sf::Vector2f&);

	virtual void move() override;
	virtual void handleCollision(GameObject&) override;

private:

};