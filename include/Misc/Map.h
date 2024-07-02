#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "Factory.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <map>

#include "StaticObjects.h"
#include "PigWarrior.h"
#include "Octorok.h"
#include "Door.h"
#include "Sign.h"
#include "BowItem.h"
#include "SwordItem.h"
#include "Link.h"
#include "Heart.h"
#include "Zelda.h"

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
	std::vector<std::unique_ptr<Enemy>>& getEnemyObjects(Link*);
	std::vector<std::unique_ptr<Inanimate>>& getInanimateObjects();
	std::vector<std::unique_ptr<StaticObjects>>& getStaticObjects(Link*);

	std::vector<std::unique_ptr<Door>>& getDoors();
	std::unique_ptr<Zelda>& getZelda();

	std::map<int, std::string> getDict() const;
	std::vector<sf::FloatRect> getStaticObjectsRects()const;

private:
	std::map<int, std::string> m_dict;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	std::vector<std::unique_ptr<Door>> m_doors;
	std::unique_ptr<Zelda> m_zelda;
	std::vector<sf::FloatRect> m_staticObjectsRects;
	std::vector<std::pair<std::string,Cell>> m_map;
};