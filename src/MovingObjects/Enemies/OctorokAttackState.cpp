#include "OctorokAttackState.h"
#include <iostream> //for debugging

OctorokAttackState::OctorokAttackState() : m_attackDuration(sf::seconds(0.3f)), m_cancelAttack(false){}

std::unique_ptr<OctorokState> OctorokAttackState::handleInput(Input input)
{
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0 || m_cancelAttack)
    {
        std::cout<<"timer done or cancel attack\n";
        return std::make_unique<OctorokStandingState>();
    }
    return nullptr;
}

void OctorokAttackState::enter(Octorok& oct)
{
    if(oct.isPushedBack()){
        m_cancelAttack = true;
        handleInput(PRESS_DOWN);
    }
	m_attackTimer.restart();
    oct.attack();
}