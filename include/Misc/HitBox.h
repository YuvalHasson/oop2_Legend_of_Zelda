#pragma once

#include <SFML/Graphics.hpp>

class HitBox{
public:
    HitBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset);

    void setPosition(const sf::Vector2f&);
    sf::Vector2f getPosition()const;

    bool checkCollision(const HitBox&)const;
    sf::FloatRect GetRect();

private: 
    sf::FloatRect m_rect;
    sf::Vector2f m_originOffset;
};