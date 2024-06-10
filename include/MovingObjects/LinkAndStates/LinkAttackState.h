#pragma once

#include "LinkState.h"

class LinkAttackState: public LinkState{
public:
    LinkAttackState();

    virtual std::unique_ptr<LinkState> handleInput(Input input)override;
    virtual void enter(Link& link) override;

private:
    sf::Clock m_attackTimer;
    sf::Time m_attackDuration;
    bool m_isAnimationSet;
};