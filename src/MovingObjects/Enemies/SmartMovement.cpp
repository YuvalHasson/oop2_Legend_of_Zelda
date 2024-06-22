#include "SmartMovement.h"
#include <iostream>

void SmartMovement::move(Input& direction, Enemy& enemy, Link* linkPtr, sf::Clock* directionChangeClock)
{
    initializeBFS(enemy.getSprite().getPosition());
    if (!m_bfsQueue.empty())
    {
        sf::Vector2f currentPosition = enemy.getSprite().getPosition();
        sf::Vector2f nextPosition = m_bfsQueue.front();
        m_bfsQueue.pop();

        // Check if the PigWarrior reached the Link
        if (isLinkAtPosition(nextPosition, linkPtr->getPosition()))
        {
            //std::cout << "Link is reached at: " << m_linkPos.x << ", " << m_linkPos.y << "\n";
            // Handle reaching the Link
            std::cout << "link get caught\n";
            // You may want to stop the PigWarrior or trigger a specific action
        }

        //// Move towards the next position
        //if (distance(currentPosition, m_linkPos) < 100.0f) {
        ////    // If the distance to the Link is small enough, move directly towards it
        //    moveTowards(m_linkPos);
        //}
        //else {
        // Otherwise, continue with the BFS algorithm
        moveTowards(enemy, linkPtr->getPosition());

        // Explore neighbors of the current position
        addNeighborsToQueue(nextPosition);
        //}
    }
    else
    {
        // If BFS queue is empty, reinitialize it to find a new path to the Link
        initializeBFS(enemy.getSprite().getPosition());
    }

    sf::Vector2i currentDirection = enemy.getDirection();
    //std::cout << "Current direction: " << currentDirection.x << ", " << currentDirection.y << "\n";
    std::cout << "Moving in direction: " << m_direction << "\n";
    if (m_direction == PRESS_RIGHT) {
        if (currentDirection != DIRECTIONS::Right) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_RIGHT), 2);
            enemy.setDirection(DIRECTIONS::Right);
            //m_direction = PRESS_RIGHT;
        }
    }
    else if (m_direction == PRESS_LEFT) {
        if (currentDirection != DIRECTIONS::Left) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_LEFT), 2);
            enemy.setDirection(DIRECTIONS::Left);
           //m_direction = PRESS_LEFT;
        }
    }
    else if (m_direction == PRESS_UP) {
        if (currentDirection != DIRECTIONS::Up) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_UP), 2);
            enemy.setDirection(DIRECTIONS::Up);
            //m_direction = PRESS_UP;
        }
    }
    else if (m_direction == PRESS_DOWN) {
        if (currentDirection != DIRECTIONS::Down) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_DOWN), 2);
            enemy.setDirection(DIRECTIONS::Down);
           // m_direction = PRESS_DOWN;
        }
    }
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
    //enter(enemy);
}

float SmartMovement::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}
