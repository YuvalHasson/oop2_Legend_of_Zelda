#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
    : m_position(position)
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

void GameObject::update()
{
    //m_sprite.setPosition(position.x * 50.0f, position.y * 50.0f);
}

void GameObject::destroy()
{
	m_destroyed = true;
}

bool GameObject::isDestroyed() const
{
    return m_destroyed;
}
