#pragma once

#include "InDestructible.h"

class Sign : public InDestructible
{
public:
	Sign(const sf::Texture&, const sf::Vector2f&);
	
	void setActive(bool);
	void draw(sf::RenderTarget&) override;
	bool checkInnerCollision(const HitBox&) const;
	void setText(const std::string&);
private:
	static bool m_registerit;
	HitBox m_hitBox; 
	sf::Text m_text;
	bool m_active;
};