#include "Map.h"

Map::Map()
{
	setDict(m_dict);
}

std::map<int, std::string> Map::getDict() const
{
	return m_dict;
}

void Map::setDict(std::map<int ,std::string>& dict)
{
	dict.emplace(0, "Wall");
	dict.emplace(1, "Octorok");
	dict.emplace(2, "PigWarrior");
	dict.emplace(3, "Boulder");
	dict.emplace(4, "Pot");
	dict.emplace(5, "WaterTile");
	dict.emplace(6, "SwordItem");
	dict.emplace(7, "BowItem");
	dict.emplace(11, "Heart");
	dict.emplace(12, "SeaUrchin");
	dict.emplace(13, "Hole");
	dict.emplace(14, "Shrub" );
	dict.emplace(15, "WizardBoss" );

	dict.emplace(50, "Door");
	dict.emplace(51, "Door");
	dict.emplace(52, "Door");
	dict.emplace(53, "Door");
	dict.emplace(54, "Door");
	dict.emplace(55, "Door");
	dict.emplace(56, "Door"); // not in use
	dict.emplace(57, "Door");
	dict.emplace(58, "Door"); // fin Dungeon entrance

	dict.emplace(100, "Sign");
	dict.emplace(101, "Sign");

}

void Map::setMap(const std::string& mapName)
{
	std::string gameMap = mapName;
	try
	{
		auto map = std::ifstream(gameMap);
		if (!map)
		{
			throw BadFileName();
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
				}
				currentCol++;
			}
			currentRow++;
		}

		// Close the file
		map.close();
	}
	catch (const BadFileName& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
}

void Map::initVector(Cell cell)
{
	auto it = m_dict.find(cell.value);
	if (it != m_dict.end())
	{
		if (it->second == "Door")
		{
			if (auto p = Factory<Door>::instance()->create(it->second, { static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row }))
			{
				if (cell.value == 50)
				{
					p->setLevelToDoor(Level::MAIN);
					p->setLinkOutPosition({ 87, 72 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 51)
				{
					p->setLevelToDoor(Level::Home);
					p->setLinkOutPosition({ 120, 137 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 52)
				{
					p->setLevelToDoor(Level::SECOND_DUNGEON);
					p->setLinkOutPosition({ 72, 138 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 53)
				{
					p->setLevelToDoor(Level::MAIN);
					p->setLinkOutPosition({ 279, 52 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 54)
				{
					p->setLevelToDoor(Level::FIRST_DUNGEON);
					p->setLinkOutPosition({ 22, 103 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 55)
				{
					p->setLevelToDoor(Level::MAIN);
					p->setLinkOutPosition({ 263, 196 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 58)
				{
					p->setLevelToDoor(Level::BOSS_DUNGEON);
					p->setLinkOutPosition({ 40, 150 });
					// p->setVictoryDoor(true); // remember to change
					m_doors.emplace_back(std::move(p));
				}
			}
			return;
		}
		if (it->second == "Sign")
		{
			if (auto p = Factory<Sign>::instance()->create(it->second, { static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row }))
			{
				if (cell.value == 100)
				{
					p->setText("Press  B  to  use  shield\nUse  the  shield  to  push  the  sea  Urchin");
					m_staticObjects.emplace_back(std::move(p));
				}
				if (cell.value == 101)
				{
					p->setText("Sharp  suprise  is  at  the  end  of  the  Dungeon");
					m_staticObjects.emplace_back(std::move(p));
				}
			}
		}
		if (auto p = Factory<StaticObjects>::instance()->create(it->second, {static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row}))
		{
			m_staticObjectsRects.emplace_back(p->getHitBox().GetRect());
			m_staticObjects.emplace_back(std::move(p));
		}
		if (auto p = Factory<Inanimate>::instance()->create(it->second, { static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row }))
		{
			m_inanimateObjects.emplace_back(std::move(p));
		}
		if (auto p = Factory<Enemy>::instance()->create(it->second, { static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row }))
		{
			m_enemyObjects.emplace_back(std::move(p));
		}
	}

}

std::vector<std::unique_ptr<Enemy>>& Map::getEnemyObjects(Link* link)
{
	//tmp create
	for (const auto& enemy : m_enemyObjects)
	{
		if (const auto& p = dynamic_cast<PigWarrior*>(enemy.get()))
		{
			p->registerAsLinkObserver(link);
		}

	}
	return m_enemyObjects;
}

std::vector<std::unique_ptr<Inanimate>>& Map::getInanimateObjects()
{
	return m_inanimateObjects;
}

std::vector<std::unique_ptr<StaticObjects>>& Map::getStaticObjects(Link* link)
{
	for (const auto& weapon : link->getAllWeapons())
	{
		if (weapon == BowWeapon)
		{
			for (const auto& staticObject : m_staticObjects)
			{
				if (const auto& p = dynamic_cast<BowItem*>(staticObject.get()))
				{
					p->destroy();
				}
			}
		}
		else if (weapon == SwordWeapon)
		{
			for (const auto& staticObject : m_staticObjects)
			{
				if (const auto& p = dynamic_cast<SwordItem*>(staticObject.get()))
				{
					p->destroy();
				}
			}
		}
	}
	//put in the map.cvs
	//if(auto p = Factory<BowItem>::instance()->create("BowItem", {25,25})){
	//	m_staticObjects.emplace_back(std::move(p));
	//}

	//if(auto p = Factory<SwordItem>::instance()->create("SwordItem", {25,45})){
	//	m_staticObjects.emplace_back(std::move(p));
	//}

	if (auto p = Factory<Heart>::instance()->create("Heart", { 25,65 })) {
		m_staticObjects.emplace_back(std::move(p));
	}
	return m_staticObjects;
}

std::vector<std::unique_ptr<Door>>& Map::getDoors()
{
	return m_doors;
}

std::vector<sf::FloatRect> Map::getStaticObjectsRects()const{
	return m_staticObjectsRects;
}