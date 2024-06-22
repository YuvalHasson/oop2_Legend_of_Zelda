#pragma once

#include "MovementStrategy.h"
#include <iostream>

class PatrolMovement : public MovementStrategy
{
public:
	PatrolMovement(Input&, sf::Clock* clock = nullptr);
	virtual std::unique_ptr<MovementStrategy> handleInput(Input) override;
	virtual void enter(Animate&) override;

private:
	Input m_direction;
	sf::Clock* m_directionChangeClock;
};