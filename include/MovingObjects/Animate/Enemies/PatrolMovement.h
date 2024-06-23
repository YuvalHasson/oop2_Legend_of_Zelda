#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"
#include <iostream>

class PatrolMovement : public MovementStrategy
{
public:
	virtual void move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock) override;

private:
	//Input m_direction;
	sf::Clock* m_directionChangeClock;
	Input m_direction;
};