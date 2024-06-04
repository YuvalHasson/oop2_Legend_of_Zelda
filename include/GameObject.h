#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

//need to include every type of game objects for collision
//or forward declare

class GameObject{
public:
    GameObject(const sf::Texture&, const sf::Vector2f&);
    virtual ~GameObject();

    virtual void draw(sf::RenderWindow&);
    bool checkCollision(const GameObject& other);

	//temp get
	sf::Sprite& getSprite() { return m_sprite; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
};