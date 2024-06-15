#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
    : m_position(position), m_previousPosition(position)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

	m_sprite.setScale(0.5f / tileSize, 1.0f / tileSize); //tmp i think
	m_sprite.setOrigin(tileSize / 2, tileSize / 2); //tmp i think
}

GameObject::~GameObject(){};

void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void GameObject::destroy()
{
	m_destroyed = true;
}

bool GameObject::isDestroyed() const
{
    return m_destroyed;
}

void GameObject::setPosition(const sf::Vector2f& pos){
    m_previousPosition = m_position;
    m_position = pos;
}

sf::Vector2f GameObject::getPreviousPosition()const{
    return m_previousPosition;
}