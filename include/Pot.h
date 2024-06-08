#pragma once

#include "Destructible.h"

class Pot : public Destructible
{
public:
	Pot(b2World&, const sf::Texture&, const sf::Vector2f&);

	void handleCollision() override;
private:

};