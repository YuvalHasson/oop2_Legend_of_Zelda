#pragma once

#include "LinkState.h"

class LinkAttackState: public LinkState{
public:
    virtual std::unique_ptr<LinkState> handleInput(Input input)override;
    virtual void enter(Link& link) override;
};