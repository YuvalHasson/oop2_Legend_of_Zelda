#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"
#include <iostream>

class Standing : public MovementStrategy
{
public:
	void move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock);
};