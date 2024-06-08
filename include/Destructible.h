#pragma once

#include "StaticObjects.h"

class Destructible : public StaticObjects
{
public:
	Destructible(b2World&, const sf::Texture&, const sf::Vector2f&);

private:
};