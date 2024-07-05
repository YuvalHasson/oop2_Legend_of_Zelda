#include "ColorAnimation.h"

ColorAnimation::ColorAnimation(const sf::Color& baseColor, float switchTime)
    :m_baseColor(baseColor), m_switchTime(switchTime), m_currentColor(1), m_timePassed(0.f)
{
        m_colors.emplace_back(baseColor);
}

void ColorAnimation::update(const sf::Time& deltaTime)
{
    m_timePassed += deltaTime.asSeconds();

    if(m_timePassed >= m_switchTime){
        m_timePassed -= m_switchTime;

        m_currentColor = (m_currentColor + 1) % m_colors.size();
    }
}

void ColorAnimation::addColorToAnimation(const sf::Color& color){
    m_colors.emplace_back(color);
}

sf::Color ColorAnimation::getCurrentColor() const{
    return m_colors[m_currentColor];
}
sf::Color ColorAnimation::getBaseColor() const{
    return m_baseColor;
}