#include "LinkAttackState.h"

LinkAttackState::LinkAttackState(): m_attackDuration(sf::seconds(0.3f)), m_isAnimationSet(false){}

std::unique_ptr<LinkState> LinkAttackState::handleInput(Input input)
{
    if(m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds()  <= 0)
    {
        return std::make_unique<LinkStandingState>();
    }   
    return nullptr;
}

void LinkAttackState::enter(Link& link)
{
    m_attackTimer.restart();
    sf::Vector2i currentDirection = link.getDirection();
    if(!m_isAnimationSet)
    {
        if(currentDirection == DIRECTIONS::Right || currentDirection == DIRECTIONS::UpRight || currentDirection == DIRECTIONS::DownRight)
        {
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackRight, 2, false , true);
        }
        else if(currentDirection == DIRECTIONS::Left || currentDirection == DIRECTIONS::UpLeft || currentDirection == DIRECTIONS::DownLeft)
        {
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackLeft, 2, false , true);
        }
        else if(currentDirection == DIRECTIONS::Down){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackDown, 3, false , true);
        }
        else if(currentDirection == DIRECTIONS::Up)
        {
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackUp, 3, false , true);
        }
        link.setAttacking(true);
    }
    link.swipeSword();
}