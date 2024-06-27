#pragma once

#include "Destructible.h"

class Shrub : public Destructible
{
public:
	Shrub(const sf::Texture&, const sf::Vector2f&);

private:
	static bool m_registerit;

};