#pragma once
#include <iostream> // debug


#include <SFML/Graphics.hpp>
#include "MovingObjects.h"
#include "StaticObjects.h"
#include "Utilities.h"
#include "Resources.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "CollisionHandling.h"

#include "Link.h"
#include "Wall.h"
#include "Pot.h"
#include "WaterTile.h"

class Board
{
public:
	Board();
	~Board() = default;

	void draw(sf::RenderWindow&);
	void addStaticObject(const sf::Vector2f);
	void makeLink();
	void move(const sf::Time&);
	void update();
	void handleCollision();
	bool setMap();
	void initVector(Cell number);


	//temp get
	const sf::Sprite& getSprite(int index) { return m_movingObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;


	// STL-like algorithm to run over all pairs
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
	{
		for (; begin != end; ++begin)
			for (auto second = begin + 1; second != end; ++second)
				fn(*begin, *second);
	}

	bool colide(GameObject& a, GameObject& b)
	{
		return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
	}
};
