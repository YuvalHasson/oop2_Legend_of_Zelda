#pragma once

#include "Projectiles.h"

class OctorokProjectile : public Projectile
{
public:
	OctorokProjectile(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void handleCollision() override;
	const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };


private:
	static bool m_registerit;
};