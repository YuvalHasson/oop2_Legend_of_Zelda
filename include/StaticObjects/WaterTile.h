#pragma once

#include "InDestructible.h"

class WaterTile : public InDestructible
{
public:
	WaterTile(const sf::Texture&, const sf::Vector2f&);

	virtual void draw(sf::RenderTarget& target)override {};

private:
	static bool m_registerit;
};