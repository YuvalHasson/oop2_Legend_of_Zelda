#pragma once
#include <iostream> // debug

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "Factory.h"
#include <memory>
#include <fstream>
#include <sstream>

class Map
{
public:
	Map();
	~Map() = default;

	void setDict(std::vector<std::string>&);

	bool setMap();
	void initVector(Cell);
	std::vector<std::unique_ptr<MovingObjects>>& getMovingObjects();
	std::vector<std::unique_ptr<StaticObjects>>& getStaticObjects();

	std::vector<std::string> getDict() const;

private:
	std::vector<std::string> m_dict;
	std::vector<std::unique_ptr<MovingObjects>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;

};