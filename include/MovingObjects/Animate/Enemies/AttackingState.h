#pragma once

#include "MovementStrategy.h"

class AttackingState : public MovementStrategy {
public:
    AttackingState();

    virtual std::unique_ptr<MovementStrategy> handleInput(Input input)override;
    virtual void enter(Animate&) override;

private:
    sf::Clock m_attackTimer;
    sf::Time m_attackDuration;
    bool m_isAnimationSet;
};