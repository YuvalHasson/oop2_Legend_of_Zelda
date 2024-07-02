#pragma once

#include "Weapon.h"

class Projectiles : public Weapon
{
public:
	Projectiles(const sf::Texture&, const sf::Vector2f&,const sf::Vector2f&, const sf::Vector2f&);

	virtual void update(const sf::Time&) = 0;
	virtual void setBool() = 0;
};