#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MovingObjects/MovingObjects.h"
#include "StaticObjects/StaticObjects.h"
#include "Misc/Utilities.h"
#include "ResourcesManager/Resources.h"
#include "ResourcesManager/SoundResource.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Misc/CollisionHandling.h"
#include "Misc/Map.h"
#include "Misc/Factory.h"
#include "Sword.h"
#include "Shield.h"
#include "Boulder.h"

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
	void setLoadedMap(std::vector<std::unique_ptr<Enemy>>&, std::vector<std::unique_ptr<Inanimate>>&);
	void initializeLevel(const Level&);
	void resetEnemiesAndInanimated();

	const Link& getLink() const;
	void setLinkPosition(const sf::Vector2f&);
	const std::vector<std::unique_ptr<Door>>& getDoors() const;

	const std::vector <std::pair<sf::Vector2f, EnemyType>> getEnemiesPositions() const;
	const std::vector<std::unique_ptr<Inanimate>>& getInanimateObjects() const;
	const std::vector<sf::FloatRect> getStaticRectsOfCurLevel() const;
	std::vector<std::unique_ptr<Inanimate>>& editInanimateObjects();
	
	// Method to extract Link object
	std::unique_ptr<Link> extractLink();
	// Method to set Link object
	void setLink(std::unique_ptr<Link>);

	bool isAttacking() const;
	const sf::Sprite& getBackground() const;

	static std::vector<sf::FloatRect> getStaticRects();

private:
	std::vector<std::unique_ptr<Enemy>> m_enemiesObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	std::vector<std::unique_ptr<Door>> m_doors;
	std::vector<sf::FloatRect> m_staticRectsOfCurLevel;
	std::unique_ptr<Link> m_link;
	std::unique_ptr<Zelda> m_zelda;

	sf::Sprite m_background;

	std::vector <std::pair<sf::Vector2f, EnemyType>> m_enemiesPositions;

	Map m_map;

	static std::vector<sf::FloatRect> m_staticRects;


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

	bool colide(GameObject&, GameObject&);
};
