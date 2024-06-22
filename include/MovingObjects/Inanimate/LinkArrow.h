#pragma once

#include "Projectiles.h"

class LinkArrow : public Projectile
{
public:
	LinkArrow(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	void initArrow(const sf::Vector2i&);

private:
	static bool m_registerit;
};