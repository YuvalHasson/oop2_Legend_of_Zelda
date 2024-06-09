#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObjects.h"
#include "StaticObjects.h"
#include "Utilities.h"
#include "Resources.h"
#include <vector>
#include <memory>

#include "CollisionHandling.h"

#include "Link.h"
#include "Wall.h"
#include "Pot.h"

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


	//temp get
	const sf::Sprite& getSprite(int index) { return m_gameObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_gameObjects; //change for moving objects
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;


	// STL-like algorithm to run over all pairs
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
	{
		for (; begin != end; ++begin)
			for (auto second = begin + 1; second != end; ++second)
				fn(*begin, *second);
	}

	template <typename Object1, typename Object2>
	bool colide(Object1& a, Object2& b)
	{
		return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
	}
};
