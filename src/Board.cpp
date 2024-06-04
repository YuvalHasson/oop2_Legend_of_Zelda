#include "Board.h"

Board::Board()
{
	addGameObject(std::make_unique<GameObject>(*Resources::getResource().getTexture(TEXTURE::Score), sf::Vector2f(10.f, 10.f)));
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->draw(window);
	}
}

void Board::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	m_gameObjects.push_back(std::move(gameObject));
}