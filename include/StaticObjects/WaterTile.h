#pragma once

#include "InDestructible.h"

class WaterTile : public InDestructible
{
public:
	WaterTile(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void handleCollision() override;
private:
	static bool m_registerit;
};