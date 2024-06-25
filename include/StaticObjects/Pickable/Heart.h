#pragma once

#include "Pickable.h"

class Heart : public Pickable
{
public:
	Heart(const sf::Texture& texture, const sf::Vector2f& position);
private:
	static bool m_registerit;
};