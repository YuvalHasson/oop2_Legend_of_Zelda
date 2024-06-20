#pragma once

#include "InDestructible.h"

class WaterTile : public InDestructible
{
public:
	WaterTile(const sf::Texture& texture, const sf::Vector2f& position);

private:
	static bool m_registerit;
};