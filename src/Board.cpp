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
	m_movingObjects.emplace_back(Factory::createOctorok(sf::Vector2f(50.f, 160.f)));
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
	std::vector<GameObject*> collision;

	// Reserve space in the collision vector to improve efficiency
	collision.reserve(m_movingObjects.size() + m_staticObjects.size());

	// Populate collision vector with raw pointers from m_gameObjects
	for (auto& obj : m_movingObjects) {
		collision.push_back(obj.get());
	}

	// Populate collision vector with raw pointers from m_staticObjects
	for (auto& obj : m_staticObjects) {
		collision.push_back(obj.get());
	}
	try
	{
		for_each_pair(collision.begin(), collision.end(), [this](GameObject* obj1, GameObject* obj2) {
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
	m_movingObjects = std::move(m_map.getMovingObjects());
	m_staticObjects = std::move(m_map.getStaticObjects());
}
