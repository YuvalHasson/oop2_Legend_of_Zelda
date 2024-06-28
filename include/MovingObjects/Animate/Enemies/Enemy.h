#pragma once

#include "Animate.h"

class Enemy : public Animate
{
public:
	Enemy(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&,const sf::Vector2f&);
	virtual sf::Vector2f getLinkPos() = 0;
	virtual std::unique_ptr<Inanimate> getAttack() = 0;
	//virtual bool switchHitBox(bool) = 0;
	//virtual void updateLineOfSight() = 0;
private:

};