#include "Link.h"

Link::Link(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(world, texture, position), m_animation({ 1, 11 }, 4, 0.1f, tileSize, tileSize)
{
}

void Link::move()
{
	sf::Clock clock;
    static bool animationInitialized = false;
    if (!animationInitialized) {
        m_animation.setStartPoisition({ 1, 11 }); // Set initial position
        m_animation.update(clock.restart()); // Update animation with elapsed time
        animationInitialized = true;
    }
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
            m_animation.update(clock.restart(), true);
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
	getSprite().setTextureRect(m_animation.getuvRect());
    m_animation.update(clock.restart());
    getSprite().setScale(1, 1);
}

void Link::handleCollision(GameObject&)
{
}
