#include "SmartMovement.h"
#include <iostream>

void SmartMovement::move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock)
{
    initializeBFS(enemy.getSprite().getPosition());
    if (!m_bfsQueue.empty())
    {
        sf::Vector2f currentPosition = enemy.getSprite().getPosition();
        sf::Vector2f nextPosition = m_bfsQueue.front();
        m_bfsQueue.pop();

        moveTowards(enemy, enemy.getLinkPos());

        // If BFS queue is empty, reinitialize it to find a new path to the Link
        addNeighborsToQueue(nextPosition);
    }

    if(directionChangeClock->getElapsedTime().asSeconds() > 0.3f){
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
        directionChangeClock->restart();
    }
    direction = m_direction;
    enemy.move();
}

void SmartMovement::initializeBFS(sf::Vector2f enemyPos)
{
    m_bfsQueue.push(enemyPos);
    m_visited.insert(enemyPos);
}

bool SmartMovement::isLinkAtPosition(const sf::Vector2f& position, const sf::Vector2f& linkPos)
{
    return position == linkPos;
}

void SmartMovement::addNeighborsToQueue(const sf::Vector2f& position)
{
    // Define potential movements (up, down, left, right)
    std::vector<sf::Vector2f> movements = {
        {1, 0},   // Right
        {-1, 0},  // Left
        {0, -1},  // Up
        {0, 1}    // Down
    };

    for (const auto& move : movements)
    {
        sf::Vector2f newPosition = position + move;

        if (m_visited.find(newPosition) == m_visited.end())
        {
            m_bfsQueue.push(newPosition);
            m_visited.insert(newPosition);
        }
    }
}

void SmartMovement::moveTowards(Enemy& enemy, const sf::Vector2f& targetPosition)
{
    sf::Vector2f direction = targetPosition - enemy.getSprite().getPosition();

    // Normalize direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }

    // Check if the PigWarrior is already close to the target position
    if (length <= 1.0f) {
        // If the PigWarrior is close enough, directly set its position to the target position
        enemy.getSprite().setPosition(targetPosition);
        return;
    }

    Input input;
    if (std::abs(direction.x) > std::abs(direction.y))
    {
        if (direction.x > 0)
        {
            input = PRESS_RIGHT;
        }
        else
        {
            input = PRESS_LEFT;
        }
    }
    else
    {
        if (direction.y > 0)
        {
            input = PRESS_DOWN;
        }
        else
        {
            input = PRESS_UP;
        }
    }
    m_direction = input;
}

float SmartMovement::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}
