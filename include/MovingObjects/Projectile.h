#pragma once

#include "Projectiles.h"

class Projectile : public Projectiles
{
public:
	Projectile(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void setBool() override{};

private:
	static bool m_registerit;
	
	sf::Clock m_timer;
};