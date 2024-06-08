#pragma once

#include "GameObject.h"

class StaticObjects : public GameObject
{
public:
	StaticObjects(b2World&, const sf::Texture&, const sf::Vector2f&);

	virtual void handleCollision() = 0;
private:

};