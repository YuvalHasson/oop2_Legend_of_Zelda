#pragma once

#include "Destructible.h"

class Pot : public Destructible
{
public:
	Pot(const sf::Texture&, const sf::Vector2f&);

private:
	static bool m_registerit;

};