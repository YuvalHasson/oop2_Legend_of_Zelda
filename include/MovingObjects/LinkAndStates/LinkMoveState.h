#pragma once

#include "LinkState.h"
#include "LinkAttackState.h"
#include "LinkStandingState.h"
#include "Link.h"

class LinkMoveState: public LinkState
{
public:
    LinkMoveState(Input);
    virtual std::unique_ptr<LinkState> handleInput(Input)override;
    virtual void enter(Link&) override;

private:
    Input m_direction;    
};