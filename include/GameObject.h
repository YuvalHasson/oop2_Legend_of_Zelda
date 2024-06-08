#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

//need to include every type of game objects for collision
//or forward declare

class GameObject{
public:
    GameObject(b2World& ,const sf::Texture&, const sf::Vector2f&);
    virtual ~GameObject();

    virtual void draw(sf::RenderWindow&);
	virtual void update();
    
	virtual void handleCollision() = 0;

    b2Body* getBody() const;

	//temp get?
	sf::Sprite& getSprite() { return m_sprite; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;

protected:
    b2Body* m_body;
};