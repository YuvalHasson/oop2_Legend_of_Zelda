#include "HitBox.h"

HitBox::HitBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
    :m_rect(position, size), m_originOffset(originOffset){}

void HitBox::setPosition(const sf::Vector2f& position){
    m_rect.left = position.x - m_originOffset.x;
    m_rect.top = position.y - m_originOffset.y;
}
sf::Vector2f HitBox::getPosition()const{
    sf::Vector2f pos(m_rect.left, m_rect.top);
    return pos;
}

bool HitBox::checkCollision(const HitBox& other)const{
    return m_rect.intersects(other.m_rect);
}

sf::FloatRect HitBox::GetRect(){
    return m_rect;
}