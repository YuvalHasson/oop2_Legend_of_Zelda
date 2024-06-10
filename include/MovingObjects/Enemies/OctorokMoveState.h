#pragma once

#include "OctorokState.h"

class OctorokMoveState: public OctorokState
{
public:
	OctorokMoveState(Input);
	virtual std::unique_ptr<OctorokState> handleInput(Input) override;
	virtual void enter(Octorok&) override;

private:
	Input m_direction;
};