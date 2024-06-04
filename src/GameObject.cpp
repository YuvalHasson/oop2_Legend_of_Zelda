#include "GameObject.h"


GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
    : m_position(position){
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

	m_sprite.setScale(0.5f / tileSize, 1.0f / tileSize); //tmp i think
	m_sprite.setOrigin(tileSize / 2, tileSize / 2); //tmp i think
}
GameObject::~GameObject(){};

void GameObject::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}

bool GameObject::checkCollision(const GameObject& other){

    return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}

