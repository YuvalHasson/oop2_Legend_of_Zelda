#pragma once
#include <iostream> // debug

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class Map
{
public:
	Map();
	~Map() = default;

	void setDict(std::vector<std::string>&);

	std::vector<std::string> getDict() const;

private:
	std::vector<std::string> m_dict;

};