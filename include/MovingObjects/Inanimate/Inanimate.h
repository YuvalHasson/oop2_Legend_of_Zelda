#pragma once

#include "MovingObjects.h"

class Inanimate : public MovingObjects
{
public:
	Inanimate(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
};