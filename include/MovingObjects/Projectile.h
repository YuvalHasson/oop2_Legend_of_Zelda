#pragma once

#include "Projectiles.h"

class Projectile : public Projectiles
{
public:
	Projectile(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;

private:
	static bool m_registerit;
};