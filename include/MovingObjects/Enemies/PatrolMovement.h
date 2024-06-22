#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"
#include <iostream>

class PatrolMovement : public MovementStrategy
{
public:
	//PatrolMovement(Input&, sf::Clock* clock = nullptr);
	//virtual std::unique_ptr<MovementStrategy> handleInput(Input) override;
	//virtual void enter(MovingObjects&) override;

	void move(Input& direction, Enemy& enemy, Link* linkPtr, sf::Clock* directionChangeClock);

private:
	//Input m_direction;
	sf::Clock* m_directionChangeClock;
	Input m_direction;
};