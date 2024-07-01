#pragma once

#include "Projectiles.h"

class LinkArrow : public Projectiles
{
public:
	LinkArrow(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void setBool() {};
	void initArrow(const sf::Vector2f&);

private:
	static bool m_registerit;
};