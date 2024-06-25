#pragma once

#include "LinkState.h"
#include "LinkAttackState.h"
#include "LinkMoveState.h"
#include "LinkShieldMovingState.h"
#include "LinkShieldStandingState.h"
#include "Link.h"

class LinkStandingState: public LinkState
{
public:
    virtual std::unique_ptr<LinkState> handleInput(Input, bool, bool) override;
    virtual void enter(Link&) override;
};