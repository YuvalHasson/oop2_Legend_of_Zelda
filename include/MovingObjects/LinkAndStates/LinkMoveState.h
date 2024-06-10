#pragma once

#include "LinkState.h"


class LinkMoveState: public LinkState{
public:
    LinkMoveState(Input);
    virtual std::unique_ptr<LinkState> handleInput(Input input)override;
    virtual void enter(Link& link) override;

private:
    Input m_direction;
    
};