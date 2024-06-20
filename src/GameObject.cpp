#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
    : m_position(position), m_previousPosition(position), m_hitBox(position,size, originOffset)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

	m_sprite.setScale(0.5f / tileSize, 1.0f / tileSize); //tmp i think
	m_sprite.setOrigin(tileSize / 2, tileSize / 2); //tmp i think
    m_hitBox.setPosition(m_position);
}

GameObject::~GameObject(){};

void GameObject::draw(sf::RenderTarget& target)
{   
    sf::RectangleShape rect;
    rect.setPosition(m_hitBox.GetRect().left, m_hitBox.GetRect().top);
    rect.setSize(sf::Vector2f(m_hitBox.GetRect().width, m_hitBox.GetRect().height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(1);
    target.draw(m_sprite);
    target.draw(rect);
}

void GameObject::destroy()
{
	m_destroyed = true;
}

bool GameObject::isDestroyed() const
{
    return m_destroyed;
}

void GameObject::setPosition(const sf::Vector2f& pos)
{
    m_previousPosition = m_position;
    m_position = pos;
    m_hitBox.setPosition(pos);
}

sf::Vector2f GameObject::getPreviousPosition() const
{
    return m_previousPosition;
}

sf::Vector2f GameObject::getPosition() const
{
    return m_position;
}

bool GameObject::checkCollision(const GameObject& other)const{
    return m_hitBox.checkCollision(other.m_hitBox);
}

HitBox GameObject::getHitBox() const
{
    return m_hitBox;
}