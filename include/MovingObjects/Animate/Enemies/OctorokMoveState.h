#pragma once

#include "OctorokState.h"
#include "OctorokStandingState.h"
#include "OctorokAttackState.h"
#include "Octorok.h"

class OctorokMoveState: public OctorokState
{
public:
	OctorokMoveState(Input);
	virtual std::unique_ptr<OctorokState> handleInput(Input) override;
	virtual void enter(Octorok&) override;

private:
	Input m_direction;
};