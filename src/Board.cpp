#include "Board.h"

#include <iostream> // debug

Board::Board()
{
}

void Board::draw(sf::RenderWindow& window, sf::FloatRect& viewBound)
{
	for (auto& gameObject : m_staticObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
			gameObject->draw(window);

	}
	for (auto& gameObject : m_movingObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
			gameObject->draw(window);
	}
}

void Board::addStaticObject(const sf::Vector2f position)
{
	m_staticObjects.emplace_back(Factory::createPot(sf::Vector2f(position.x + 25.f, position.y)));
}

void Board::makeLink()
{
	m_movingObjects.emplace_back(Factory::createLink(sf::Vector2f(32.f, 50.f)));
	m_movingObjects.emplace_back(Factory::createOctorok(sf::Vector2f(150.f, 150.f)));
}

void Board::move(const sf::Time& deltaTime)
{
	for (auto& gameObject : m_movingObjects)
	{
		gameObject->move(deltaTime);
		gameObject->attack(deltaTime); //might need to be somewhere else
	}
}

void Board::update()
{
	for (auto& gameObject : m_movingObjects)
	{
		gameObject->update();
	}

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
}

void Board::handleCollision()
{
	try
	{
		// Handle collisions among moving objects
		for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});

		// Handle collisions between moving and static objects
		for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool Board::setMap()
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

void Board::initVector(Cell cell)
{
	// texture of daungeon path
	if (cell.value <= -1610612618 && cell.value >= -1610612666 || cell.value == 1610613065 || cell.value == 1610613107)
	{
		return;

	}
	//texture of border
	if (cell.value > 100000 || cell.value < -100000)
	{
		m_staticObjects.emplace_back(Factory::createWall(sf::Vector2f(tileSize * cell.col, tileSize * cell.row)));
		return;
	}
	std::string value = m_map.getDict()[cell.value];
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
