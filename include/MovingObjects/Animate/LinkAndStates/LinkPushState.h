#pragma once

#include "LinkState.h"
#include "LinkAttackState.h"
#include "LinkStandingState.h"
#include "LinkShieldMovingState.h"
#include "Link.h"

class LinkPushState : public LinkState
{
public:
	LinkPushState(Input);
	virtual std::unique_ptr<LinkState> handleInput(Input, bool, bool) override;
	virtual void enter(Link&) override;
private:
	Input m_direction;
};