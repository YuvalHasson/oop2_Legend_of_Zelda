#pragma once

//pushable object

#include "MovingObjects.h"

class Boulder : public MovingObjects
{
public:
	Boulder(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void handleCollision() override;

private:
	static bool m_registerit;
};