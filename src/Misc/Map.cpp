#include "Map.h"


Map::Map()
{
	setDict(m_dict);
	setMap();
}

std::map<int, std::string> Map::getDict() const
{
	return m_dict;
}

void Map::setDict(std::map<int ,std::string>& dict)
{
	dict.emplace(264 ,"wall");
	dict.emplace(265, "wall");
	dict.emplace(267, "wall");
	dict.emplace(268, "wall");
	dict.emplace(269, "wall" );
	dict.emplace(270, "wall" );
	dict.emplace(274, "wall" );
	dict.emplace(275, "wall" );
	dict.emplace(288, "wall" );
	dict.emplace(290, "wall" );
	dict.emplace(291, "wall" );
	dict.emplace(292, "wall" );
	dict.emplace(293, "wall" );
	dict.emplace(312, "wall" );
	dict.emplace(313, "wall" );
	dict.emplace(339, "wall" );
	dict.emplace(340, "wall" );
	dict.emplace(253, "flowers" );
	dict.emplace(229, "flowers" );
	dict.emplace(152, "tree" );
	dict.emplace(153, "tree" );
	dict.emplace(154, "tree" );
	dict.emplace(176, "tree" );
	dict.emplace(117, "tree" );
	dict.emplace(200, "tree" );
	dict.emplace(201, "tree" );
	dict.emplace(130, "tree" );
	dict.emplace(131, "tree" );
	dict.emplace(155, "tree" );
	dict.emplace(255, "tree" );
	dict.emplace(249, "tree" );
	dict.emplace(49, "house" );
	dict.emplace(60, "house" );
	dict.emplace(61, "house" );
	dict.emplace(62, "house" );
	dict.emplace(9, "house" );
	dict.emplace(10, "house" );
	dict.emplace(11, "house" );
	dict.emplace(33, "house" );
	dict.emplace(34, "house" );
	dict.emplace(35, "house" );
	dict.emplace(48, "house" );
	dict.emplace(476, "sea" );
	dict.emplace(477, "sea" );
	dict.emplace(478, "sea" );
	dict.emplace(479, "sea" );
	dict.emplace(-1610612467, "wall" );
	dict.emplace(1610613065, "wall" );
	dict.emplace(1610613006, "wall" );
	dict.emplace(1610613010, "wall" );
	dict.emplace(1610613001, "wall" );
	dict.emplace(1610613003, "wall" );
	dict.emplace(-1610612468, "wall" );
	dict.emplace(-1073741536, "wall" );
	dict.emplace(-1073741511, "wall" );
	dict.emplace(-1610612461, "wall" );
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
	m_enemyObjects.clear();
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
	m_staticObjects = Factory::createStaticObjects(m_map);
	m_enemyObjects = Factory::createEnemies(); // probobly change

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
	////texture of border
	//if (cell.value > 100000 || cell.value < -100000)
	//{
	//	//m_staticObjects.emplace_back(Factory::createWall(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
	//	return;
	//}
	//std::cout << m_dict[cell.value] << "\n";
	auto it = m_dict.find(cell.value);
	if (it != m_dict.end())
	{
		m_map.emplace_back(std::make_pair(it->second, cell));
	}
	//std::string value = m_dict[cell.value];
	//if (value == "wall" || value == "tree" ||
	//	value == "flowers" || value == "house")
	//{
	//	//m_staticObjects.emplace_back(Factory::createWall(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
	//}
	//else if (value == "sea")
	//{
	//	//m_staticObjects.emplace_back(Factory::createWaterTile(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
	//}
}

std::vector<std::unique_ptr<Enemy>>& Map::getEnemyObjects()
{
	return m_enemyObjects;
}

std::vector<std::unique_ptr<StaticObjects>>& Map::getStaticObjects()
{
	return m_staticObjects;
}
