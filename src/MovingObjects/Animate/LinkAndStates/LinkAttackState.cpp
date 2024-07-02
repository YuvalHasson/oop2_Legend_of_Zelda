#include "LinkAttackState.h"

LinkAttackState::LinkAttackState(): m_attackDuration(sf::seconds(0.3f)), m_isAnimationSet(false){}

std::unique_ptr<LinkState> LinkAttackState::handleInput(Input input, bool, bool)
{

    if(m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds()  <= 0)
    {
        if(input == PRESS_DOWN_LEFT  || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT||
            input == PRESS_UP_RIGHT  || input == PRESS_LEFT       || input == PRESS_RIGHT  ||
            input == PRESS_DOWN      || input == PRESS_UP){
                return std::make_unique<LinkMoveState>(input);        
        }
        else{
            return std::make_unique<LinkStandingState>();
        }
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
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackRight, 2 , true);
        }
        else if(currentDirection == DIRECTIONS::Left || currentDirection == DIRECTIONS::UpLeft || currentDirection == DIRECTIONS::DownLeft)
        {
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackLeft, 2 , true);
        }
        else if(currentDirection == DIRECTIONS::Down){
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackDown, 3 , true);
        }
        else if(currentDirection == DIRECTIONS::Up)
        {
            link.setGraphics(ANIMATIONS_POSITIONS::LinkAttackUp, 3 , true);
        }
        link.setAttacking(true);
    }
    if(link.getCurrentWeapon() == SwordWeapon)
    {
        link.swipeSword();
    }
    else if(link.getCurrentWeapon() == BowWeapon)
    {
        link.shoot();
    }
}