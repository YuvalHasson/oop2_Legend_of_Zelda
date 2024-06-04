#include "GameObject.h"


GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
    : m_position(position){
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
}
GameObject::~GameObject(){};

void GameObject::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}

bool GameObject::checkCollision(const GameObject& other){

    return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}

