#pragma once

#include "Destructible.h"

class Lock : public Destructible
{
public:
	Lock(const sf::Texture&, const sf::Vector2f&);

private:
	static bool m_registerit;
};