#pragma once

#include "MovingObjects.h"
#include "Animation.h"

class Link : public MovingObjects
{
public:
	Link(b2World&, const sf::Texture&, const sf::Vector2f&);

	virtual void move(const sf::Time& deltaTime) override;
	virtual void handleCollision(GameObject&) override;

private:
	Animation m_animation;
	sf::Vector2i m_direction;
};