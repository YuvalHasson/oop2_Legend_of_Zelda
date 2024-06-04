#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Utilities.h"
#include "Resources.h"
#include <vector>
#include <memory>

class Board
{
public:
	Board();
	~Board() = default;

	void draw(sf::RenderWindow&);
	void addGameObject(std::unique_ptr<GameObject> gameObject);

	//temp get
	sf::Sprite& getSprite(int index) { return m_gameObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<GameObject>> m_gameObjects; //change for moving objects
};
