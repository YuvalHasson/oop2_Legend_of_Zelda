#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"

class PatrolMovement : public MovementStrategy
{
public:
	PatrolMovement() :m_direction(PRESS_RIGHT) {}
	virtual void move(Input&, Enemy&, sf::Clock*) override;

private:
	sf::Clock* m_directionChangeClock;
	Input m_direction;
};