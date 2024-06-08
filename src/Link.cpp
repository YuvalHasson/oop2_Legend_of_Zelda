#include "Link.h"

#include <iostream> //debugging

Link::Link(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(world, texture, position), m_animation({ 1, 42 }, 2, 0.15f, tileSize, tileSize), m_direction(0,0)
{
    
}

void Link::move(const sf::Time& deltaTime)
{

    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);

    b2Vec2 velocity(0.f, 0.f);

    bool isMoving = false;

    // Check for diagonal movement first
    if (up && right)
    {
        if (m_direction != sf::Vector2i(1, -1))
        {
            m_animation.setAnimation(sf::Vector2u{69, 42}, 2);
            m_direction = sf::Vector2i(1, -1);
        }
        velocity.x += 1.f;
        velocity.y -= 1.f;
        isMoving = true;
    }
    else if (up && left)
    {
        if (m_direction != sf::Vector2i(-1, -1))
        {
            m_animation.setAnimation(sf::Vector2u{35, 11}, 2);
            m_direction = sf::Vector2i(-1, -1);
        }
        velocity.x -= 1.f;
        velocity.y -= 1.f;
        isMoving = true;
    }
    else if (down && right)
    {
        if (m_direction != sf::Vector2i(1, 1))
        {
            m_animation.setAnimation(sf::Vector2u{69, 42}, 2);
            m_direction = sf::Vector2i(1, 1);
        }
        velocity.x += 1.f;
        velocity.y += 1.f;
        isMoving = true;
    }
    else if (down && left)
    {
        if (m_direction != sf::Vector2i(-1, 1))
        {
            m_animation.setAnimation(sf::Vector2u{35, 11}, 2);
            m_direction = sf::Vector2i(-1, 1);
        }
        velocity.x -= 1.f;
        velocity.y += 1.f;
        isMoving = true;
    }

    // Check for single direction movement
    if (!isMoving)
    {
        if (up)
        {
            if (m_direction != sf::Vector2i(0, -1))
            {
                m_animation.setAnimation(sf::Vector2u{35, 42}, 2);
                m_direction = sf::Vector2i(0, -1);
            }
            velocity.y -= 1.f;
            isMoving = true;
        }
        if (down)
        {
            if (m_direction != sf::Vector2i(0, 1))
            {
                m_animation.setAnimation(sf::Vector2u{1, 42}, 2);
                m_direction = sf::Vector2i(0, 1);
            }
            velocity.y += 1.f;
            isMoving = true;
        }
        if (left)
        {
            if (m_direction != sf::Vector2i(-1, 0))
            {
                m_animation.setAnimation(sf::Vector2u{35, 11}, 2);
                m_direction = sf::Vector2i(-1, 0);
            }
            velocity.x -= 1.f;
            isMoving = true;
        }
        if (right)
        {
            if (m_direction != sf::Vector2i(1, 0))
            {
                m_animation.setAnimation(sf::Vector2u{69, 42}, 2);
                m_direction = sf::Vector2i(1, 0);
            }
            velocity.x += 1.f;
            isMoving = true;
        }
    }
    if(isMoving){
        m_animation.update(deltaTime);
    }
    m_body->SetLinearVelocity(velocity);

    
	getSprite().setTextureRect(m_animation.getuvRect());
    getSprite().setScale(1, 1);
}

void Link::handleCollision(GameObject&)
{
}
