#pragma once

#include "LinkState.h"
#include "LinkAttackState.h"
#include "LinkMoveState.h"
#include "LinkShieldMovingState.h"
#include "Link.h"

class LinkShieldStandingState: public LinkState
{
public:
    virtual std::unique_ptr<LinkState> handleInput(Input, bool) override;
    virtual void enter(Link&) override;
};