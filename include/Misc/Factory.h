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

typedef std::map<std::string, std::unique_ptr<GameObject>(*)(const sf::Vector2f&)> mymap;

class Factory
{
public:
	static std::vector<std::unique_ptr<StaticObjects>> createStaticObjects(const std::vector<std::pair<std::string, Cell>>&);
	static std::unique_ptr<Link> createLink();
	static std::vector<std::unique_ptr<Enemy>> createEnemies();

	static std::unique_ptr<GameObject> create(const std::string& name, const sf::Vector2f& position);
	static bool registerit(const std::string& name, std::unique_ptr<GameObject>(*)(const sf::Vector2f&));
private:
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};