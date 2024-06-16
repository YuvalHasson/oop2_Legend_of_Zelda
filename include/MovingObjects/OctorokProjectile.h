#pragma once

#include "Projectiles.h"

class OctorokProjectile : public Projectile
{
public:
	OctorokProjectile(const sf::Texture&, const sf::Vector2f&);
private:
	static bool m_registerit;
};