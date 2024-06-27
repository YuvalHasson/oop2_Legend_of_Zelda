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

	void draw(sf::RenderTarget&, sf::FloatRect&);
	void addProjectileToMoving();
	void makeLink();
	void update(const sf::Time&);
	void handleCollision();
	void setMap();
	void initializeLevel(const Level&);
	void resetEnemiesAndInanimated();

	const Link& getLink() const { return *m_link; }
	void setLinkPosition(const sf::Vector2f& pos) { m_link->setPosition(pos); }
	const std::vector<std::unique_ptr<Door>>& getDoors() const { return m_doors; }

	// Method to extract Link object
	std::unique_ptr<Link> extractLink() {
		return std::move(m_link); // Transfer ownership
	}

	// Method to set Link object
	void setLink(std::unique_ptr<Link> link) {
		m_link = std::move(link); // Transfer ownership
	}	

	bool isAttacking() const;
	const sf::Sprite& getBackground() const;

private:
	std::vector<std::unique_ptr<Enemy>> m_enemiesObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	std::vector<std::unique_ptr<Door>> m_doors;
	std::unique_ptr<Link> m_link;

	sf::Sprite m_background;

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
		return a.checkCollision(b);
	}
};
