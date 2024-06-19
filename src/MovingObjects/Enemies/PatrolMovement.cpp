#include "PatrolMovement.h"
#include "StandingState.h"

PatrolMovement::PatrolMovement(Input& direction, sf::Clock* directionChangeClock) : m_direction(direction), m_directionChangeClock(directionChangeClock)
{
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    std::cout << "here" << std::endl;
    //if (directionChangeClock->getElapsedTime().asSeconds() >= 1.0f) // Change direction every 2 seconds
    //{
        int randomMovment = rand() % 4;

        std::cout << "randomMovment: " << randomMovment << std::endl;

        switch (randomMovment)
        {
        case 0:
            up = true;
            break;
        case 1:
            down = true;
            break;
        case 2:
            right = true;
            break;
        case 3:
            left = true;
            break;
        default:
            break;
        }
        directionChangeClock->restart();
 /*   }*/

    if (up) {
        m_direction = PRESS_UP;
    }
    else if (down) {
        m_direction = PRESS_DOWN;
    }
    else if (right) {
        m_direction = PRESS_RIGHT;
    }
    else if (left) {
        m_direction = PRESS_LEFT;
    }
    direction = m_direction;
}

std::unique_ptr<MovementStrategy> PatrolMovement::handleInput(Input input)
{
    //if (input == PRESS_DOWN_LEFT || input == PRESS_DOWN_RIGHT || input == PRESS_UP_LEFT ||
    //    input == PRESS_UP_RIGHT || input == PRESS_LEFT || input == PRESS_RIGHT || input == PRESS_DOWN ||
    //    input == PRESS_UP) {
    //    return std::make_unique<PatrolMovement>(input);
    //}
   
    return std::make_unique<PatrolMovement>(input, m_directionChangeClock);
}

void PatrolMovement::enter(MovingObjects& object)
{
    sf::Vector2i currentDirection = object.getDirection();
    //std::cout << "Current direction: " << currentDirection.x << ", " << currentDirection.y << "\n";
    //std::cout << "Moving in: " << m_directionChangeClock.getElapsedTime().asSeconds() << "\n";
    if (m_direction == PRESS_RIGHT) {
        if (currentDirection != DIRECTIONS::Right) {
            
            object.setGraphics(object.getAnimationTexturePosition(PRESS_RIGHT), 2);
            object.setDirection(DIRECTIONS::Right);
        }
    }
    else if (m_direction == PRESS_LEFT) {
        if (currentDirection != DIRECTIONS::Left) {
            object.setGraphics(object.getAnimationTexturePosition(PRESS_LEFT), 2);
            object.setDirection(DIRECTIONS::Left);
        }
    }
    else if (m_direction == PRESS_UP) {
        if (currentDirection != DIRECTIONS::Up) {
            object.setGraphics(object.getAnimationTexturePosition(PRESS_UP), 2);
            object.setDirection(DIRECTIONS::Up);
        }
    }
    else if (m_direction == PRESS_DOWN) {
        if (currentDirection != DIRECTIONS::Down) {
            object.setGraphics(object.getAnimationTexturePosition(PRESS_DOWN), 2);
            object.setDirection(DIRECTIONS::Down);
        }
    }

    object.move();
}