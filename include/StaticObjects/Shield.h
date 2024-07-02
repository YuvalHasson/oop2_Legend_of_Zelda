#pragma once

#include "InDestructible.h"

class Shield: public InDestructible{
public:
    Shield(const sf::Texture&, const sf::Vector2f&);

    void activate(const sf::Vector2f&, const sf::Vector2i&);
    void deActivate();
    bool getActive() const;
    void setActive(bool);
    bool getCollided();
    sf::Vector2i getCollisionDirection() const;
	sf::Vector2i getLinkDirection() const;
    void pushBack(const sf::Vector2i&);
    
private:
    bool m_active;
    bool m_collided;
	sf::Vector2i m_linkDirection;
    sf::Vector2i m_collisionDirection;
    static bool m_registerit;
};