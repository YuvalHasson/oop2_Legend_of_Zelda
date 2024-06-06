#include "Board.h"

Board::Board()
{
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->draw(window);
	}
}

void Board::addGameObject(std::unique_ptr<MovingObjects> gameObject)
{
	m_gameObjects.push_back(std::move(gameObject));
}

void Board::makeLink(b2World& world)
{
	addGameObject(std::make_unique<Link>(world, *Resources::getResource().getTexture(TEXTURE::Link), sf::Vector2f(10.f, 10.f)));
}

void Board::move()
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->move();
	}
}

void Board::update()
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->update();
	}
}
