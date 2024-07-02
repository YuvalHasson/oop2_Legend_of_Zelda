#pragma once

#include <SFML/Graphics.hpp>

class HitBox{
public:
    HitBox(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

    void setPosition(const sf::Vector2f&);
    sf::Vector2f getPosition() const;

    bool checkCollision(const HitBox&) const;
    sf::FloatRect GetRect();
    void setBox(const sf::Vector2f&, const sf::Vector2f&);

private: 
    sf::FloatRect m_rect;
    sf::Vector2f m_originOffset;
};