#pragma once

#include "Projectiles.h"

class LinkArrow : public Projectile
{
public:
	LinkArrow(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void handleCollision() override;
	void initArrow(const sf::Vector2i&);
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };

private:
	static bool m_registerit;
};