#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "Utilities.h"

class GameObject;
class StaticObjects;
class Enemy;
class Link;
class MovingObjects;
class Sword;
class OctorokProjectile;
class Boulder;
class LinkArrow;

typedef std::map<std::string, std::unique_ptr<GameObject>(*)(const sf::Vector2f&)> mymap;

class Factory
{
public:
	static std::vector<std::unique_ptr<StaticObjects>> createStaticObjects(const std::vector<std::pair<std::string, Cell>>&);
	static std::unique_ptr<Link> createLink();
	static std::vector<std::unique_ptr<MovingObjects>> createEnemies();
	static std::unique_ptr<Sword> createSword();
	static std::unique_ptr<OctorokProjectile> createOctorokProjectile();
	static std::unique_ptr<LinkArrow> createLinkArrow();
	static std::vector<std::unique_ptr<MovingObjects>> createBoulder();
	static std::unique_ptr<GameObject> create(const std::string& name, const sf::Vector2f& position);
	static bool registerit(const std::string& name, std::unique_ptr<GameObject>(*)(const sf::Vector2f&));
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};