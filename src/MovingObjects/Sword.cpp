#include "Sword.h"
#include <iostream>//debugging

bool Sword::m_registerit = Factory::registerit("Sword",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> {
        return std::make_unique<Sword>(*Resources::getResource().getTexture(TEXTURE::Link), position);
    });



Sword::Sword(const sf::Texture& texture, const sf::Vector2f& position)
    : MovingObjects(texture, position, sf::Vector2f(12,12), sf::Vector2f(12/2, 12/2)), m_active(false){}
    
void Sword::activate(const sf::Vector2f& position, const sf::Vector2i& direction){
    m_active = true;
    //set sword position
    getSprite().setPosition(position);
    setDirection(direction);

    //make sprite visible
    sf::Color color = getSprite().getColor();
    color.a = 255;
    getSprite().setColor(color);

    sf::Vector2f attackPos;
    //set sword position and animation according to direction and link position
    if(direction.x == 1){
        setGraphics(ANIMATIONS_POSITIONS::SwordRight, 2, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x + tileSize * 0.8f;
        attackPos.y = position.y;
    }
    else if(direction.x == -1){
        setGraphics(ANIMATIONS_POSITIONS::SwordLeft, 2, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x - tileSize * 0.8f;
        attackPos.y = position.y;
    }
    else if(direction == DIRECTIONS::Up){
        setGraphics(ANIMATIONS_POSITIONS::SwordUp, 3, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x;
        attackPos.y = position.y - tileSize * 0.8f;
    }
    else if(direction == DIRECTIONS::Down){
        setGraphics(ANIMATIONS_POSITIONS::SwordDown, 3, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x ;
        attackPos.y = position.y + tileSize * 0.8f;
    }
    getSprite().setPosition(attackPos);
    setPosition(attackPos);
}

void Sword::deActivate(){
    m_active = false;

    //make sprite invisible
    sf::Color color = getSprite().getColor();
    color.a = 0;
    getSprite().setColor(color);
}

bool Sword::getActive()const{
    return m_active;
}
void Sword::setActive(bool active){
    m_active = active; 
}

void Sword::update(const sf::Time& deltaTime){
        updateGraphics(deltaTime);
        updateSprite();
}
void Sword::handleCollision(){

}