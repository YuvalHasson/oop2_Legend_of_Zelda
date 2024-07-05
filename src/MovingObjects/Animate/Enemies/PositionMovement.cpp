#include "PositionMovement.h"

void PositionMovement::move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock)
{
    //direction before normalizing
    sf::Vector2f directionVec = m_destination - enemy.getPosition();
    
    //normalizing the direction vector
    float length = std::sqrt(directionVec.x * directionVec.x + directionVec.y * directionVec.y);
    if (length != 0) {
        directionVec.x /= length;
        directionVec.y /= length;
    }

    sf::Vector2i headedDirection(static_cast<int>(std::round(directionVec.x)), static_cast<int>(std::round(directionVec.y)));
    
    if (directionChangeClock->getElapsedTime().asSeconds() >= 0.1f)
    {
        if(headedDirection.x == 1){
            m_direction = PRESS_RIGHT;
        }
        else if(headedDirection.x == -1){
            m_direction = PRESS_LEFT;
        }
        else if(headedDirection.y == 1){
            m_direction = PRESS_DOWN;
        }
        else if(headedDirection.y == -1){
            m_direction = PRESS_UP;
        }
        else if(headedDirection.x == 0 && headedDirection.y == 0){
            m_direction = STANDING;
        }
        directionChangeClock->restart();
        direction = m_direction;
    }

    sf::Vector2f currentDirection = enemy.getDirection();
    if (m_direction == PRESS_RIGHT) {
        if (currentDirection != DIRECTIONS::Right) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_RIGHT), 2);
            enemy.setDirection(DIRECTIONS::Right);
        }
    }
    else if (m_direction == PRESS_LEFT) {
        if (currentDirection != DIRECTIONS::Left) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_LEFT), 2);
            enemy.setDirection(DIRECTIONS::Left);
        }
    }
    else if (m_direction == PRESS_UP) {
        if (currentDirection != DIRECTIONS::Up) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_UP), 2);
            enemy.setDirection(DIRECTIONS::Up);
        }
    }
    else if (m_direction == PRESS_DOWN) {
        if (currentDirection != DIRECTIONS::Down) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_DOWN), 2);
            enemy.setDirection(DIRECTIONS::Down);
        }
    }
    enemy.move();
}

void PositionMovement::setDestination(const sf::Vector2f& destination){
    m_destination = destination;
}