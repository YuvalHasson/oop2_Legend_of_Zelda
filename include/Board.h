#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObjects.h"
#include "Utilities.h"
#include "Resources.h"
#include <vector>
#include <memory>

#include "Link.h"

class Board
{
public:
	Board();
	~Board() = default;

	void draw(sf::RenderWindow&);
	void addGameObject(std::unique_ptr<MovingObjects> gameObject);
	void makeLink(b2World& world);
	void move(const sf::Time& deltaTime);
	void update();

	//temp get
	sf::Sprite& getSprite(int index) { return m_gameObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_gameObjects; //change for moving objects
};
