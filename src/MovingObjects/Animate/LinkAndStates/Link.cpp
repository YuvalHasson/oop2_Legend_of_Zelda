#include "Link.h"

#include <iostream> //debugging

bool m_registerit = Factory<Link>::instance()->registerit("Link",
    [](const sf::Vector2f& position) -> std::unique_ptr<Link>
	{
		return std::make_unique<Link>(*Resources::getResource().getTexture(TEXTURE::Link), position);
	});

Link::Link(const sf::Texture& texture, const sf::Vector2f& position)
	: Animate(texture, position, sf::Vector2f(7,7.5f),
    sf::Vector2f(tileSize/4.5f, tileSize / 9)),
    m_state(std::make_unique<LinkStandingState>()),
    m_sword(Factory<Sword>::instance()->create("Sword", { 0,0 })),m_arrow(nullptr),
    m_shield(Factory<Shield>::instance()->create("Shield", { 0,0 })),
    m_isPushing(false), m_isShooting(false), m_wasTabPressed(false),
    m_isShielding(false), m_invincible(false),
    m_currentWeapon(0)
{
    getSprite().setOrigin(tileSize/2, tileSize/2);
    setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2);
    updateSprite();
    setHp(MAX_HEALTH);
    //hitanimation color
    addHitColor(sf::Color(255,93,0));
    addHitColor(sf::Color(255,255,255,0));
}

Link::~Link()
{
    NotifyObserversLinkOut();
}

void Link::update(const sf::Time& deltaTime){
    Input input;
    bool up     = sf::Keyboard::isKeyPressed(sf::Keyboard::Up)      || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down   = sf::Keyboard::isKeyPressed(sf::Keyboard::Down)    || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool right  = sf::Keyboard::isKeyPressed(sf::Keyboard::Right)   || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool left   = sf::Keyboard::isKeyPressed(sf::Keyboard::Left)    || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool space  = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    bool tab    = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    bool b      = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
    
    //check for shield
    if(b){
        m_isShielding = true;
        m_shield->activate(getPosition(), getDirection());
    }
    else{
        m_isShielding = false;
        m_shield->deActivate();
    }
    if(m_shield->getCollided()){
        pushBack(m_shield->getCollisionDirection());
    }

    if(space)
    {   
        if(!m_weapons.empty())//can enter attack state
            input = PRESS_SPACE;
        else
            input = NONE;
    }
    else if(down && right)
    {
        input = PRESS_DOWN_RIGHT;
    }
    else if(down && left)
    {
        input = PRESS_DOWN_LEFT;
    }
    else if(up && right)
    {
        input = PRESS_UP_RIGHT;
    }
    else if(up && left)
    {
        input = PRESS_UP_LEFT;
    }
    else if(up)
    {
        input = PRESS_UP;
    }
    else if(down)
    {
        input = PRESS_DOWN;
    }
    else if(right)
    {
        input = PRESS_RIGHT;
    }
    else if(left)
    {
        input = PRESS_LEFT;
    }
    else
    {
        input = NONE;
    }
    if(tab && !m_wasTabPressed){
        if(!m_weapons.empty()){
            m_currentWeapon = (m_currentWeapon + 1) % m_weapons.size();
        }
    }

    m_wasTabPressed = tab;

    //update color animation
    if(getInvincible()){
        Animate::updateHitAnimation(deltaTime);
        getSprite().setColor(getCurrentColor());
    }
    else{
        getSprite().setColor(getBaseColor());
    }

    //handle state switching
    std::unique_ptr<LinkState> state = m_state->handleInput(input, m_isShielding, isPush());

    if(state)
    {
        m_state = std::move(state);
        m_state->enter(*this);
    }   
    if(!dynamic_cast<LinkStandingState*>(m_state.get()) && !dynamic_cast<LinkShieldStandingState*>(m_state.get()))
    {
        updateGraphics(deltaTime);
    }

    if(!(m_timeSinceLastPush.getElapsedTime().asSeconds() - 0.01f <= 0)){
        setPush(false);
    }

    //update sword
    m_sword->update(deltaTime);

    //update sprite
    updateSprite();
	setSpeed(1.f);
}

void Link::move()
{
    Animate::move();
    NotifyObservers();
}

void Link::swipeSword()
{
    if(m_sword)
    {
        m_sword->activate(getSprite().getPosition(), getDirection());
    }
}
void Link::stopSwordSwipe()
{
    if(m_sword)
    {
        m_sword->deActivate();
    }
    setAttacking(false);
}

bool Link::getInvincible() 
{
    if(m_invincibleTimer.getElapsedTime().asSeconds() - invincibilityTime.asSeconds() >= 0){
        m_invincible = false;
    }
    return m_invincible;
}

void Link::initializeInvincible()
{
    if(!m_invincible){
        m_invincible = true;
        m_invincibleTimer.restart();
    }
}

Sword* Link::getSword(){
    if(m_attacking && m_sword){
        return m_sword.get();
    }
    return nullptr;
}

Shield* Link::getShield(){
    if(m_isShielding){
        return m_shield.get();
    }
    return nullptr;
}

void Link::draw(sf::RenderTarget& target){
    GameObject::draw(target);
    m_sword->draw(target);
    m_shield->draw(target);
}
void Link::setPush(bool isPushing)
{
	m_isPushing = isPushing;
}

bool Link::isPush() const
{
    return m_isPushing;
}

bool Link::getShooting() const
{
    return m_isShooting;
}

void Link::stopShooting()
{
    setAttacking(false);
}

void Link::shoot()
{
    setAttacking(true);
}

std::unique_ptr<Inanimate> Link::getAttack()
{
    if(m_attacking && getCurrentWeapon() == BowWeapon){
        if(auto p = Factory<LinkArrow>::instance()->create("LinkArrow", getPosition())){
            m_arrow = std::move(p);
            m_arrow->setPosition(sf::Vector2f(getPosition().x, getPosition().y + 3));
            m_arrow->getSprite().setPosition(sf::Vector2f(getPosition().x, getPosition().y + 3));
            m_arrow->initArrow(getDirection());
        }
        stopShooting();
        return std::move(m_arrow);
    }
    return nullptr;
}


void Link::takeSword(){
    m_weapons.emplace_back(SwordWeapon);
}

void Link::takeBow(){
    m_weapons.emplace_back(BowWeapon);
}

Weapons Link::getCurrentWeapon()const{
    if(!m_weapons.empty()){
        return m_weapons[m_currentWeapon];
    }
    return NoWeapon;
}

void Link::resetTimeSinceLastPushed(){
    m_timeSinceLastPush.restart();
}

//-------------observer list functions--------------
void Link::RegisterObserver(LinkObserver* observer){
    m_observers.emplace_back(observer);
}

void Link::RemoveObserver(LinkObserver* observer){
    m_observers.erase(remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Link::NotifyObservers(){
    for(const auto& observer: m_observers){
        observer->updateLinkPosition(getPosition());
    }
}

void Link::NotifyObserversLinkOut() const
{
    for (const auto& observer : m_observers) {
        observer->removeLink();
    }
}

