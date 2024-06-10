#pragma once
#include <iostream> // debug

#include <SFML/Graphics.hpp>
#include "MovingObjects/MovingObjects.h"
#include "StaticObjects/StaticObjects.h"
#include "Misc/Utilities.h"
#include "ResourcesManager/Resources.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Misc/CollisionHandling.h"
#include "Misc/Map.h"
#include "Misc/Factory.h"


class Board
{
public:
	Board();
	~Board() = default;

	void draw(sf::RenderWindow&, sf::FloatRect&);
	void addStaticObject(const sf::Vector2f);
	void makeLink();
	void move(const sf::Time&);
	void update(const sf::Time& deltaTime);
	void handleCollision();
	void setMap();
	void initVector(Cell number);

	//temp get
	const sf::Sprite& getSprite(int index) { return m_movingObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	Map m_map;


	// STL-like algorithm to run over all pairs within the same range
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
	{
		for (; begin != end; ++begin)
			for (auto second = begin + 1; second != end; ++second)
				fn(*begin, *second);
	}

	// STL-like algorithm to run over all pairs between two different ranges
	template <typename FwdIt1, typename FwdIt2, typename Fn>
	void for_each_pair(FwdIt1 begin1, FwdIt1 end1, FwdIt2 begin2, FwdIt2 end2, Fn fn)
	{
		for (; begin1 != end1; ++begin1)
			for (auto second = begin2; second != end2; ++second)
				fn(*begin1, *second);
	}

	bool colide(GameObject& a, GameObject& b)
	{
		return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
	}
};
