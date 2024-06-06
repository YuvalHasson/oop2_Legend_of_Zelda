#include "Link.h"

Link::Link(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(world, texture, position), m_animation({ 1, 42 }, 2, 0.15f, tileSize, tileSize), m_direction(0,0)
{
    
}

void Link::move(const sf::Time& deltaTime)
{
	
    if (sf::Event::KeyPressed)
    {
        
        b2Vec2 velocity(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(m_direction != sf::Vector2i(0,-1)){
                m_animation.setStartPoisition(sf::Vector2u{35,42});
                m_animation.setImageCount(2);
                m_direction = sf::Vector2i(0,-1);
            }
            m_animation.update(deltaTime);
            velocity.y -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(m_direction != sf::Vector2i(0,1)){
                m_animation.setStartPoisition(sf::Vector2u{1,42});
                m_animation.setImageCount(2);
                m_direction = sf::Vector2i(0,1);
            }
            m_animation.update(deltaTime);
            velocity.y += 1.f;
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(m_direction != sf::Vector2i(1,0)){
                m_animation.setStartPoisition(sf::Vector2u{35,11});
                m_animation.setImageCount(2);
                m_direction = sf::Vector2i(1,0);
            }
            m_animation.update(deltaTime);
            velocity.x -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(m_direction != sf::Vector2i(-1,0)){
                m_animation.setStartPoisition(sf::Vector2u{69,42});
                m_animation.setImageCount(2);
                m_direction = sf::Vector2i(-1,0);
            }
            m_animation.update(deltaTime);
            velocity.x += 1.f;
        }
        m_body->SetLinearVelocity(velocity);
    }
    
	getSprite().setTextureRect(m_animation.getuvRect());
    getSprite().setScale(1, 1);
}

void Link::handleCollision(GameObject&)
{
}
