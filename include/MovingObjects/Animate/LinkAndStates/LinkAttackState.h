#pragma once

#include "LinkState.h"
#include "Link.h"
#include "Utilities.h"

class LinkAttackState: public LinkState
{
public:
    LinkAttackState();

    virtual std::unique_ptr<LinkState> handleInput(Input)override;
    virtual void enter(Link&) override;

private:
    sf::Clock m_attackTimer;
    sf::Time m_attackDuration;
    bool m_isAnimationSet;
};