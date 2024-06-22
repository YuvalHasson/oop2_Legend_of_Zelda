#pragma once

#include "OctorokState.h"
#include "OctorokMoveState.h"
#include "OctorokAttackState.h"
#include "Octorok.h"

class OctorokStandingState: public OctorokState
{
public:
	virtual std::unique_ptr<OctorokState> handleInput(Input) override;
	virtual void enter(Octorok&) override;
};