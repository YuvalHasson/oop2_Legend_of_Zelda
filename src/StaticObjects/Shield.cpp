#include "Shield.h"
#include <iostream>

bool Shield::m_registerit = Factory<Shield>::instance()->registerit("Shield",
    [](const sf::Vector2f& position) -> std::unique_ptr<Shield>
    {
        return std::make_unique<Shield>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
    });

Shield::Shield(const sf::Texture& texture, const sf::Vector2f& position)
    :InDestructible(texture, position, sf::Vector2f(9,2), sf::Vector2f(9/2, 2/2)), m_collided(false){
    
    getSprite().setColor(sf::Color::Transparent);
    getSprite().setScale(0.8f, 0.8f);
}


void Shield::activate(const sf::Vector2f& linkPosition, const sf::Vector2i& linkDirection){
    m_active = true;
    
    float width = getHitBox().GetRect().width;
    float height = getHitBox().GetRect().height;

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f offset;
    if(linkDirection.x == -1){
        //change the hitbox to face left
        size.x = 2;
        size.y = 9;
        offset.x = 11/2 + 5;
        offset.y = 4/2;
        position = linkPosition;
    }
    else if(linkDirection.x == 1){
        //change the hitbox to face right
        size.x = 2;
        size.y = 9;
        offset.x = 11/2 - 14;
        offset.y = 4/2;
        position = linkPosition;
    }
    else{
        offset.x = 9/2;
        offset.y = 1;
        if(linkDirection == DIRECTIONS::Up){
            //change hitbox to face up
            size.x = 9;
            size.y = 2;
            position.x = linkPosition.x;
            position.y = linkPosition.y - 7;
        }
        else if(linkDirection == DIRECTIONS::Down){
            //change hitbox to face down
            size.x = 9;
            size.y = 2;
            position.x = linkPosition.x;
            position.y = linkPosition.y+ 9;
        }
    }
    setHitBox(size, offset);
    setPosition(position);

}

void Shield::deActivate(){
    m_active = false;
    m_collided = false;
}

bool Shield::getActive()const{
    return m_active;
}

void Shield::setActive(bool active){
    m_active = active;
}


bool Shield::getCollided(){
    if(m_collided){
        m_collided = false;
        return true;
    }
    return m_collided;
}

sf::Vector2i Shield::getCollisionDirection() const{
    return m_collisionDirection;
}

void Shield::pushBack(const sf::Vector2i& direction){
    m_collided = true;
    m_collisionDirection = direction;
}