#pragma once

#include "InDestructible.h"

class Hole : public InDestructible
{
public:
	Hole(const sf::Texture&, const sf::Vector2f&);
private:
	static bool m_registerit;
};