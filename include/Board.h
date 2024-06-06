#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObjects.h"
#include "StaticObjects.h"
#include "Utilities.h"
#include "Resources.h"
#include <vector>
#include <memory>

#include "Link.h"
#include "Wall.h"

class Board
{
public:
	Board();
	~Board() = default;

	void draw(sf::RenderWindow&);
	void addGameObject(std::unique_ptr<MovingObjects> gameObject);
	void addStaticObject(b2World&);
	void makeLink(b2World&);
	void move(const sf::Time&);
	void update();

	//temp get
	const sf::Sprite& getSprite(int index) { return m_gameObjects[index]->getSprite(); }

private:
	std::vector<std::unique_ptr<MovingObjects>> m_gameObjects; //change for moving objects
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
};
