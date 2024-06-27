#pragma once

#include "InDestructible.h"

class Sign : public InDestructible
{
public:
	Sign(const sf::Texture&, const sf::Vector2f&);
	
	void setActive(bool);
	void draw(sf::RenderTarget&) override;
	bool getInnerBox(const HitBox&) const;

private:
	static bool m_registerit;
	HitBox m_hitBox; 
	bool m_active;
};