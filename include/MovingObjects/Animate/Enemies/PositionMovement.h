#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"

class PositionMovement : public MovementStrategy
{
public:
	PositionMovement() = default;
	virtual void move(Input&, Enemy&, sf::Clock*) override;
    void setDestination(const sf::Vector2f&);

private:
	sf::Clock* m_directionChangeClock;
	Input m_direction;
    sf::Vector2f m_destination;
};