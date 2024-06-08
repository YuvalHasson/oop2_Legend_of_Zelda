#include "Board.h"

#include <iostream> // debug

Board::Board()
{
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& gameObject : m_staticObjects)
	{
		gameObject->draw(window);

	}
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->draw(window);
	}
}

void Board::addStaticObject(b2World& world, const sf::Vector2f position)
{
	m_staticObjects.emplace_back(std::make_unique<Wall>(world, *Resources::getResource().getResource().getTexture(TEXTURE::Score), position));
	m_staticObjects.emplace_back(std::make_unique<Pot>(world, *Resources::getResource().getResource().getTexture(TEXTURE::MapObjects), sf::Vector2f(position.x + 25.f, position.y)));
}

void Board::makeLink(b2World& world)
{
	m_gameObjects.emplace_back(std::make_unique<Link>(world, *Resources::getResource().getTexture(TEXTURE::Link), sf::Vector2f(20.f, 20.f)));
}

void Board::move(const sf::Time& deltaTime)
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->move(deltaTime);
		gameObject->attack(deltaTime); //might need to be somewhere else
	}
}

void Board::update()
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->update();
	}

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
}

void Board::handleCollision()
{
	for (auto& gameObject : m_gameObjects)
	{
		for (auto& staticObj : m_staticObjects)
		{
			if (colide(*gameObject, *staticObj))
			{
				processCollision(*gameObject, *staticObj);
			}
			if (colide(*staticObj, *gameObject))
			{
				processCollision(*staticObj, *gameObject);
			}
		}
	}
}
