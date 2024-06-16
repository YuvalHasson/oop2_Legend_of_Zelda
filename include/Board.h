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
	Board(Board&& other) noexcept; // Move constructor
	Board& operator=(Board&& other) noexcept; // Move assignment operator

	~Board() = default;

	void draw(sf::RenderWindow&, sf::FloatRect&);
	void addStaticObject();
	void makeLink();
	void move(const sf::Time&);
	void update(const sf::Time& deltaTime);
	void handleCollision();
	void setMap();

	//temp get
	const Link& getSprite() const { return *m_link; }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_movingObjects;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	std::unique_ptr<Link> m_link;
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
