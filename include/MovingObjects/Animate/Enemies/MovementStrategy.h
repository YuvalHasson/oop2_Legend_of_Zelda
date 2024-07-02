#pragma once

#include "Utilities.h"
#include <memory>
#include "MovingObjects.h"
#include "Enemy.h"
#include "Link.h"
#include "Animate.h"

class MovementStrategy
{
public:
	virtual ~MovementStrategy() = default;
	virtual void move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock) = 0;
	// ...
};