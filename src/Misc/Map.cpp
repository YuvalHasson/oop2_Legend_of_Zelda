
#include "Map.h"

Map::Map()
{
	setDict(m_dict);
	setMap();
}

std::vector<std::string> Map::getDict() const
{
	return m_dict;
}

void Map::setDict(std::vector<std::string>& dict)
{
	dict.resize(1000);
	dict[264] = { "wall" };
	dict[265] = { "wall" };
	dict[267] = { "wall" };
	dict[268] = { "wall" };
	dict[269] = { "wall" };
	dict[270] = { "wall" };
	dict[274] = { "wall" };
	dict[275] = { "wall" };
	dict[288] = { "wall" };
	dict[290] = { "wall" };
	dict[291] = { "wall" };
	dict[292] = { "wall" };
	dict[293] = { "wall" };
	dict[312] = { "wall" };
	dict[313] = { "wall" };
	dict[339] = { "wall" };
	dict[340] = { "wall" };
	dict[253] = { "flowers" };
	dict[229] = { "flowers" };
	dict[152] = { "tree" };
	dict[153] = { "tree" };
	dict[154] = { "tree" };
	dict[176] = { "tree" };
	dict[177] = { "tree" };
	dict[200] = { "tree" };
	dict[201] = { "tree" };
	dict[130] = { "tree" };
	dict[131] = { "tree" };
	dict[155] = { "tree" };
	dict[225] = { "tree" };
	dict[249] = { "tree" };
	dict[49] = { "house" };
	dict[60] = { "house" };
	dict[61] = { "house" };
	dict[62] = { "house" };
	dict[9] = { "house" };
	dict[10] = { "house" };
	dict[11] = { "house" };
	dict[33] = { "house" };
	dict[34] = { "house" };
	dict[35] = { "house" };
	dict[48] = { "house" };
	dict[476] = { "sea" };
	dict[477] = { "sea" };
	dict[478] = { "sea" };
	dict[479] = { "sea" };

}

bool Map::setMap()
{
	std::string gameMap = "Map.csv";

	auto map = std::ifstream(gameMap);
	if (!map)
	{
		std::cerr << "Error opening file: " << gameMap << std::endl;
		return true; // can be changed to exeptions
	}
	m_movingObjects.clear();
	m_staticObjects.clear();

	std::string line;
	// Read the file line by line
	int currentRow = 0;
	while (std::getline(map, line)) {
		std::istringstream lineStream(line);
		std::string cell;
		int currentCol = 0;

		// Parse each line into comma-separated values
		while (std::getline(lineStream, cell, ',')) {
			// Convert the cell to an integer
			int value = std::stoi(cell);
			Cell c = { value, currentRow, currentCol };
			if (c.value != -1)
			{
				initVector(c);
				//std::cout << value << " ";
			}
			currentCol++;
		}
		currentRow++;
	}
	// Close the file
	map.close();
	return true;
}

void Map::initVector(Cell cell)
{
	// texture of daungeon path
	if (cell.value <= -1610612618 && cell.value >= -1610612666 || cell.value == 1610613065 || cell.value == 1610613107 || cell.value == -1073741688)
	{
		return;
	}
	//texture of border
	if (cell.value > 100000 || cell.value < -100000)
	{
		m_staticObjects.emplace_back(Factory::createWall(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
		return;
	}
	std::string value = m_dict[cell.value];
	if (value == "wall" || value == "tree" ||
		value == "flowers" || value == "house")
	{
		m_staticObjects.emplace_back(Factory::createWall(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
	}
	else if (value == "sea")
	{
		m_staticObjects.emplace_back(Factory::createWaterTile(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
	}
}

std::vector<std::unique_ptr<MovingObjects>>& Map::getMovingObjects()
{
	return m_movingObjects;
}

std::vector<std::unique_ptr<StaticObjects>>& Map::getStaticObjects()
{
	return m_staticObjects;
}
