#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Factory.h"
#include "HitBox.h"

class GameObject
{
public:
    GameObject(const sf::Texture&, const sf::Vector2f& ,const sf::Vector2f&, const sf::Vector2f&);
    virtual ~GameObject();

    virtual void draw(sf::RenderTarget&);
    
    void destroy();
    bool isDestroyed() const;
    void setPosition(const sf::Vector2f&);
    sf::Vector2f getPreviousPosition() const;
	sf::Vector2f getPosition() const;

    bool checkCollision(const GameObject& other)const;

    HitBox getHitBox(); // for debugging

	//temp get?
	sf::Sprite& getSprite() { return m_sprite; }


private:
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    sf::Vector2f m_previousPosition;

    bool m_destroyed = false;
    HitBox m_hitBox;
};