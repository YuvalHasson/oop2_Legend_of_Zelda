#include "Link.h"

#include <iostream> //debugging

bool Link::m_registerit = Factory::registerit("Link",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> {
        return std::make_unique<Link>(*Resources::getResource().getTexture(TEXTURE::Link), position);
    });

Link::Link(const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(texture, position, sf::Vector2f(7,7), sf::Vector2f(tileSize/5, tileSize / 6)), m_state(std::make_unique<LinkStandingState>()),
      m_sword(nullptr), m_isPushing(false)
{
    setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2);
    updateSprite();
    setHp(6);
}

void Link::handleCollision()
{

}

void Link::update(const sf::Time& deltaTime){

    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    
    Input input;
    if(space){
        input = PRESS_SPACE;
    }
    else if(down && right){
        input = PRESS_DOWN_RIGHT;
    }
    else if(down && left){
        input = PRESS_DOWN_LEFT;
    }
    else if(up && right){
        input = PRESS_UP_RIGHT;
    }
    else if(up && left){
        input = PRESS_UP_LEFT;
    }
    else if(up){
        input = PRESS_UP;
    }
    else if(down){
        input = PRESS_DOWN;
    }
    else if(right){
        input = PRESS_RIGHT;
    }
    else if(left){
        input = PRESS_LEFT;
    }
    else{
        input = NONE;
    }
    
    std::unique_ptr<LinkState> state = m_state->handleInput(input);

    if(state){
        m_state = std::move(state);
        m_state->enter(*this);

    }   
    if(!dynamic_cast<LinkStandingState*>(m_state.get())){
        updateGraphics(deltaTime);
    }
    updateSprite();
}

void Link::insertSword(Sword* sword){
    m_sword = sword;
}

void Link::swipeSword(){
    if(m_sword){
        m_sword->activate(getSprite().getPosition(), getDirection());
    }
}
void Link::stopSwordSwipe(){
    if(m_sword){
        m_sword->deActivate();
    }
}

bool Link::getInvincible()const{
    return m_invincibleTimer.getElapsedTime().asSeconds() - invincibilityTime.asSeconds() <= 0;
}

void Link::initializeInvincible(){
    m_invincibleTimer.restart();
}

void Link::setPush(bool isPushing)
{
	m_isPushing = isPushing;
}

bool Link::isPush() const
{
    return m_isPushing;
}
