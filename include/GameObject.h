#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"


class GameObject{
public:
    GameObject(const sf::Texture&, const sf::Vector2f&);
    virtual ~GameObject();

    virtual void draw(sf::RenderWindow&);
    
	virtual void handleCollision() = 0;

    void destroy();
    bool isDestroyed() const;

	//temp get?
	sf::Sprite& getSprite() { return m_sprite; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;

    bool m_destroyed = false;
};