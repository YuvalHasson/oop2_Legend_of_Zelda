#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"
#include <iostream>

class PositionMovement : public MovementStrategy
{
public:
	virtual void move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock) override;
    void setDestination(const sf::Vector2f&);
private:
	//Input m_direction;
	sf::Clock* m_directionChangeClock;
	Input m_direction;
    sf::Vector2f m_destination;
};