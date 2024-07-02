#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"

class Standing : public MovementStrategy
{
public:
	void move(Input&, Enemy&, sf::Clock*);
};