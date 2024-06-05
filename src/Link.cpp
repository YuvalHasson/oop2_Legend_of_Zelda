#include "Link.h"

Link::Link(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(world, texture, position)
{
}

void Link::move()
{
    if (sf::Event::KeyPressed)
    {
        b2Vec2 velocity(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity.y -= 2.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity.y += 2.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x -= 2.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x += 2.f;
        }
        m_body->SetLinearVelocity(velocity);
    }
}

void Link::handleCollision(GameObject&)
{
}
