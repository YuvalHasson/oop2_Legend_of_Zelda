#include "Board.h"

#include <iostream> // debug

Board::Board()
{
}

Board::Board(Board&& other) noexcept
	: m_enemies(std::move(other.m_enemies)), m_staticObjects(std::move(other.m_staticObjects))
	, m_link(std::move(other.m_link))
{
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other)
	{
		m_enemies = std::move(other.m_enemies);
		m_staticObjects = std::move(other.m_staticObjects);
		m_link = std::move(other.m_link);
	}
	return *this;
}

void Board::draw(sf::RenderWindow& window, sf::FloatRect& viewBound)
{
	for (auto& gameObject : m_staticObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
			gameObject->draw(window);

	}
	m_link->draw(window);
	for (auto& enemy : m_enemies)
	{
		if (enemy->getSprite().getGlobalBounds().intersects(viewBound))
			enemy->draw(window);
	}
}

void Board::addStaticObject()
{
	//m_staticObjects = Factory::createStaticObjects();
}

void Board::makeLink()
{
	m_link = Factory::createLink();
}

void Board::move(const sf::Time& deltaTime)
{
	//for (auto& gameObject : m_movingObjects)
	//{
	//	// gameObject->move(deltaTime);
	//	// gameObject->attack(deltaTime); //might need to be somewhere else
	//}
}

void Board::update(const sf::Time& deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		enemy->update(deltaTime);
	}

	m_link->update(deltaTime);

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
	std::erase_if(m_enemies, [](const auto& enemy) { return enemy->isDestroyed(); });
}

void Board::handleCollision()
{
	try
	{
		//link and static objects
		for (const auto& staticObjects : m_staticObjects)
		{
			if (colide(*m_link, *staticObjects))
			{
				processCollision(*m_link, *staticObjects);
			}
		}
		//link and enemies
		for (const auto& enemy : m_enemies)
		{
			if (colide(*m_link, *enemy))
			{
				processCollision(*m_link, *enemy);
			}
		}

		// Handle collisions among moving objects
		for_each_pair(m_enemies.begin(), m_enemies.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});

		// Handle collisions between moving and static objects
		for_each_pair(m_enemies.begin(), m_enemies.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
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

void Board::setMap()
{
	m_enemies = std::move(m_map.getEnemyObjects());
	m_staticObjects = std::move(m_map.getStaticObjects());
}
