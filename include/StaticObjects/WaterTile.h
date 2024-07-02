#pragma once

#include "InDestructible.h"

class WaterTile : public InDestructible
{
public:
	WaterTile(const sf::Texture&, const sf::Vector2f&);

private:
	static bool m_registerit;
};