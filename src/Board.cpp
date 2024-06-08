#include "Board.h"

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

void Board::addGameObject(std::unique_ptr<MovingObjects> gameObject)
{
	m_gameObjects.emplace_back(std::move(gameObject));
}

void Board::addStaticObject(b2World& world)
{
	m_staticObjects.emplace_back(std::make_unique<Wall>(world, *Resources::getResource().getResource().getTexture(TEXTURE::Score), sf::Vector2f(90.f, 90.f)));
}

void Board::makeLink(b2World& world)
{
	addGameObject(std::make_unique<Link>(world, *Resources::getResource().getTexture(TEXTURE::Link), sf::Vector2f(90.f, 90.f)));
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
}
