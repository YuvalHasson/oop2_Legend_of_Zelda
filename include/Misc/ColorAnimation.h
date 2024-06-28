#pragma once

#include <SFML/Graphics.hpp>

class ColorAnimation{
public:
    ColorAnimation(){};
    
    //when creating gets the default color of the sprite
    ColorAnimation(const sf::Color&, float switchTime = 0.06f);

    void update(const sf::Time& deltaTime);
    void addColorToAnimation(const sf::Color&);
    sf::Color getCurrentColor()const;
    sf::Color getBaseColor()const;

private:
    sf::Color m_baseColor;
    std::vector<sf::Color> m_colors;
    size_t m_currentColor;

    float m_timePassed;
    float m_switchTime;
};