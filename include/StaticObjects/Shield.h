#pragma once

#include "InDestructible.h"

class Shield: public InDestructible{
public:
    Shield(const sf::Texture&, const sf::Vector2f&);

    void activate(const sf::Vector2f&, const sf::Vector2f& direction);
    void deActivate();
    bool getActive()const;
    void setActive(bool active);
    bool getCollided();
    sf::Vector2f getCollisionDirection() const;
	sf::Vector2f getLinkDirection() const;
    void pushBack(const sf::Vector2f&);
    
private:
    bool m_active;
    bool m_collided;
	sf::Vector2f m_linkDirection;
    sf::Vector2f m_collisionDirection;
    static bool m_registerit;
};