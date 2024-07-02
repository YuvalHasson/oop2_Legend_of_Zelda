#include "Shield.h"

bool Shield::m_registerit = Factory<Shield>::instance()->registerit("Shield",
    [](const sf::Vector2f& position) -> std::unique_ptr<Shield>
    {
        return std::make_unique<Shield>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
    });

Shield::Shield(const sf::Texture& texture, const sf::Vector2f& position)
    :InDestructible(texture, position, sf::Vector2f(9,2), sf::Vector2f(9/2, 2/2)),
    m_collided(false), m_active(false)
{
    getSprite().setColor(sf::Color::Transparent);
}


void Shield::activate(const sf::Vector2f& linkPosition, const sf::Vector2f& linkDirection){
    m_active = true;
	m_linkDirection = linkDirection;
    m_active        = true;

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f offset;
    if(m_linkDirection.x == -1){
        //change the hit-box to face left
        size.x = 2;
        size.y = 9;
        offset.x = 11/2 + 5;
        offset.y = 4.f / 2.f;
        position = linkPosition;
    }
    else if(m_linkDirection.x == 1){
        //change the hit-box to face right
        size.x = 2;
        size.y = 9;
        offset.x = 11/2 - 14;
        offset.y = 4.f / 2.f;
        position = linkPosition;
    }
    else{
        offset.x = 9.f / 2.f;
        offset.y = 1;
        if(m_linkDirection == DIRECTIONS::Up){
            //change hit-box to face up
            size.x = 9;
            size.y = 2;
            position.x = linkPosition.x;
            position.y = linkPosition.y - 7;
        }
        else if(m_linkDirection == DIRECTIONS::Down){
            //change hit-box to face down
            size.x = 9;
            size.y = 2;
            position.x = linkPosition.x;
            position.y = linkPosition.y + 9;
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

sf::Vector2f Shield::getCollisionDirection() const
{
    return m_collisionDirection;
}

sf::Vector2f Shield::getLinkDirection() const
{
    return m_linkDirection;
}

void Shield::pushBack(const sf::Vector2f& direction){
    m_collided = true;
    m_collisionDirection = direction;
}