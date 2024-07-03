#pragma once

#include "InDestructible.h"

class Wall : public InDestructible
{
public:
	Wall(const sf::Texture&, const sf::Vector2f&);

	virtual void draw(sf::RenderTarget&)override {};
	
private:
	static bool m_registerit;
};