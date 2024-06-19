#pragma once

#include "MovementStrategy.h"

class StandingState : public MovementStrategy
{
public:
	virtual std::unique_ptr<MovementStrategy> handleInput(Input) override;
	virtual void enter(MovingObjects&) override;

};