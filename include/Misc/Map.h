#pragma once
#include <iostream> // debug

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "Factory.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <map>

#include "StaticObjects.h"
#include "PigWarrior.h"
#include "Octorok.h"

#include "BadFileName.h"

class Link;

class Map
{
public:
	Map();
	~Map() = default;

	void setDict(std::map<int, std::string>&);

	void setMap(const std::string&);
	void initVector(Cell);
	std::vector<std::unique_ptr<Animate>>& getEnemyObjects(Link*);
	std::vector<std::unique_ptr<StaticObjects>>& getStaticObjects();

	std::map<int, std::string> getDict() const;

private:
	std::map<int, std::string> m_dict;
	std::vector<std::unique_ptr<Animate>> m_enemyObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;

	std::vector<std::pair<std::string,Cell>> m_map;
};