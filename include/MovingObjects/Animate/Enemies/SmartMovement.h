#pragma once

#include "MovementStrategy.h"
#include "Enemy.h"
#include <queue>
#include <set>

struct Vector2fComparator{
	bool operator()(const sf::Vector2f & lhs, const sf::Vector2f & rhs) const {
		if (lhs.x != rhs.x) {
			return lhs.x < rhs.x;
		}
		return lhs.y < rhs.y;
	}
};

class SmartMovement : public MovementStrategy
{
public:
	SmartMovement() = default;
	virtual void move(Input&, Enemy&, sf::Clock*) override;

	void initializeBFS(sf::Vector2f);
	bool isLinkAtPosition(const sf::Vector2f&, const sf::Vector2f&);
	void addNeighborsToQueue(const sf::Vector2f&);
	void moveTowards(Enemy&, const sf::Vector2f&);

	//void UpdateLinkPos(const sf::Vector2f& position);
	float distance(const sf::Vector2f&, const sf::Vector2f&);

private:
	std::queue<sf::Vector2f> m_bfsQueue;
	std::set<sf::Vector2f, Vector2fComparator> m_visited;
	Input m_direction;
};