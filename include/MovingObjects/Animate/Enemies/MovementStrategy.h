#pragma once

#include "Utilities.h"
#include <memory>
#include "Animate.h"

class MovementStrategy
{
public:

	virtual ~MovementStrategy() = default;
	virtual std::unique_ptr<MovementStrategy> handleInput(Input) = 0;
	virtual void enter(Animate&) = 0;
	// ...
};