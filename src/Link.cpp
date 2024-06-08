#include "Link.h"

#include <iostream> //debugging

Link::Link(b2World& world, const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(world, texture, position), m_animation({ 1, 42 }, 2, 0.15f, tileSize, tileSize), m_direction(0,0)
{
    
}

void Link::move(const sf::Time& deltaTime)
{
    
    if(m_attacking){
        return;
    }

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
            m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkRight, 2);
            m_direction = sf::Vector2i(1, -1);
        }
        isMoving = true;
    }
    else if (up && left)
    {
        if (m_direction != sf::Vector2i(-1, -1))
        {
            m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkLeft, 2);
            m_direction = sf::Vector2i(-1, -1);
        }
        isMoving = true;
    }
    else if (down && right)
    {
        if (m_direction != sf::Vector2i(1, 1))
        {
            m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkRight, 2);
            m_direction = sf::Vector2i(1, 1);
        }
        isMoving = true;
    }
    else if (down && left)
    {
        if (m_direction != sf::Vector2i(-1, 1))
        {
            m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkLeft, 2);
            m_direction = sf::Vector2i(-1, 1);
        }
        isMoving = true;
    }

    // Check for single direction movement
    if (!isMoving)
    {
        if (up)
        {
            if (m_direction != sf::Vector2i(0, -1))
            {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkUp, 2);
                m_direction = sf::Vector2i(0, -1);
            }
            isMoving = true;
        }
        if (down)
        {
            if (m_direction != sf::Vector2i(0, 1))
            {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkDown, 2);
                m_direction = sf::Vector2i(0, 1);
            }
            isMoving = true;
        }
        if (left)
        {
            if (m_direction != sf::Vector2i(-1, 0))
            {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkLeft, 2);
                m_direction = sf::Vector2i(-1, 0);
            }
            isMoving = true;
        }
        if (right)
        {
            if (m_direction != sf::Vector2i(1, 0))
            {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkRight, 2);
                m_direction = sf::Vector2i(1, 0);
            }
            isMoving = true;
        }
    }
    if(isMoving){
        m_animation.update(deltaTime);
        velocity.x = m_direction.x;
        velocity.y = m_direction.y;

    }
    m_body->SetLinearVelocity(velocity);

    
	updateSprite(m_animation.getuvRect());
}

void Link::attack(const sf::Time& deltaTime){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!m_attacking) {
            m_attacking = true;
            //attack to left
            if (m_direction.x == -1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackLeft, 2, false, true);
            }
            //attack to right
            else if (m_direction.x == 1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackRight, 2, false, true);
            }
            //attack down
            else if (m_direction.x == 0 && m_direction.y == 1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackDown, 3, false, true);
            }
            //attack up
            else if (m_direction.x == 0 && m_direction.y == -1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackUp, 3, false, true);
            }

            // Need to also create a sword object 
        }
    }

    if (m_attacking) {
        m_animation.update(deltaTime);

        if (m_animation.isDone()) {
            m_attacking = false;

            // Reset animation after attack is done
            if (m_direction.x == 1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkRight, 2);
            } else if (m_direction.x == -1) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkLeft, 2);
            } else if (m_direction == sf::Vector2i(0, -1)) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkUp, 2);
            } else if (m_direction == sf::Vector2i(0, 1)) {
                m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkDown, 2);
            }
        }
    }
    updateSprite(m_animation.getuvRect());
}

void Link::handleCollision()
{
    //std::cout << "geet\n";
}
