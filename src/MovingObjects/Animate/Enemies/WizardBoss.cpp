#include "WizardBoss.h"
#include <cmath>

#include <iostream> // Debug

bool WizardBoss::m_registerit = Factory<Enemy>::instance()->registerit("WizardBoss",
    [](const sf::Vector2f& position) -> std::unique_ptr<Enemy>
    {
        return std::make_unique<WizardBoss>(*Resources::getResource().getTexture(TEXTURE::Boss), position);
    });

WizardBoss::WizardBoss(const sf::Texture& texture, const sf::Vector2f& position)
    :Enemy(texture, position, sf::Vector2f(12.f * 0.8f, 12.f * 0.8f), sf::Vector2f(-2, -2)),
     m_currInput(PRESS_RIGHT),
     m_moveStrategy(std::make_unique<SmartMovement>()), 
     m_attackStrategy(std::make_unique<Stab>()),
     m_weapon(nullptr), m_invincible(false), m_isDead(false)
{
    setDirection(DIRECTIONS::Down);
    setGraphics(ANIMATIONS_POSITIONS::BossDown, 2, true);
    updateSprite();
    setHp(10);
    
}

WizardBoss::~WizardBoss()
{
    if (m_link)
    {
        m_link->RemoveObserver(this);
    }
}

void WizardBoss::update(const sf::Time& deltaTime)
{

    if(m_isDead){
        return;
    }
    Enemy::updateHitAnimation(deltaTime);
    Enemy::update(deltaTime);
    
    sf::Vector2f currentPosition = getSprite().getPosition();

    //setPhase
    if (!isShootingPhase()) {

        setMoveStrategy(std::make_unique<SmartMovement>());
        setAttackStrategy(std::make_unique<Stab>());
        if (distance(currentPosition, m_linkPos) < 28.0f) {

            PerformAttack();
            m_weapon->setBool();
        }
    }
    else{
        auto p = dynamic_cast<PositionMovement*>(m_moveStrategy.get());
        auto s = dynamic_cast<Standing*>(m_moveStrategy.get());

        if(!p && !s){
            auto posmove = std::make_unique<PositionMovement>();
            posmove->setDestination(sf::Vector2f(160,160)); //NEED TO CHANGE THE DESTINATION WHEN WE HAVE A LEVEL
            setMoveStrategy(std::move(posmove));
            m_invincible = true;
            m_shootingPhase = true;
            m_shootingPhaseTimer.restart();
        }
        //5x5 pixels threshold from the desired position
        auto sh = dynamic_cast<Shoot*>(m_attackStrategy.get());
        if((getPosition().x< 165 && getPosition().x > 155) && (getPosition().y< 165 && getPosition().y > 155) && !sh){
            setAttackStrategy(std::make_unique<Shoot>());
            setMoveStrategy(std::make_unique<Standing>());
            setGraphics(ANIMATIONS_POSITIONS::BossDown,2);
            m_shootIntervalTimer.restart();
        }
        if(m_shootingPhaseTimer.getElapsedTime() >= shootingPhaseDuration){
            m_shootingPhase = false;
            m_invincible = false;
            setHp(getHp() - 1);
            setDirection({0,0});

        }
        
    }
    if(m_shootingPhase && m_shootIntervalTimer.getElapsedTime() >= shootInterval){
        //function to shoot in a circle based on specific time interval

        PerformAttack();
        m_weapon->setBool();
        m_shootIntervalTimer.restart();

        sf::Vector2f startDirection = getDirection();
        sf::Vector2f newDirection;
        newDirection.x = static_cast<float>(startDirection.x * std::cos(M_PI/8) - startDirection.y * std::sin(M_PI/8));
        newDirection.y = static_cast<float>(startDirection.x * std::sin(M_PI/8) + startDirection.y * std::cos(M_PI/8));
        setDirection(newDirection);
    }

    PerformMove();
    updateGraphics(deltaTime);
    updateSprite();
    if (getHp() <= MIN_HEALTH)
    {
        setDead();
        // destroy();
    }
	setSpeed(1.f);
}


const sf::Vector2u& WizardBoss::getAnimationTexturePosition(Input side)
{
    switch (side)
    {
    case PRESS_UP:
        return ANIMATIONS_POSITIONS::BossUp;
    case PRESS_DOWN:
        return ANIMATIONS_POSITIONS::BossDown;
    case PRESS_LEFT:
        return ANIMATIONS_POSITIONS::BossLeft;
    case PRESS_RIGHT:
        return ANIMATIONS_POSITIONS::BossRight;
    default:
        return ANIMATIONS_POSITIONS::BossDown; //will never get here
    }
}

sf::Vector2f WizardBoss::getLinkPos()
{
    return m_linkPos;
}

void WizardBoss::attack()
{
    setAttacking(true);
}

void WizardBoss::PerformMove()
{
    m_moveStrategy->move(m_currInput, *this, &m_directionChangeClock);
}

void WizardBoss::setAttackStrategy(std::unique_ptr<AttackStrategy> attack)
{
    m_attackStrategy = std::move(attack);
}

void WizardBoss::PerformAttack()
{
    m_attackDuration = sf::seconds(2.f);
    m_attackStrategy->attack(m_attackDuration, m_attackTimer, m_weapon, *this);

}

std::unique_ptr<Inanimate> WizardBoss::getAttack()
{
    setAttacking(false);
    if(m_weapon){
        return std::move(m_weapon);
    }
    else{
        return nullptr;
    }
}

bool WizardBoss::getInvincible()const{
    return m_invincible;
}

bool WizardBoss::isShootingPhase()const{
    return getHp() % 4 == 0;
}

void WizardBoss::setMoveStrategy(std::unique_ptr<MovementStrategy> move)
{
    m_moveStrategy = std::move(move);
}

float WizardBoss::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

EnemyType WizardBoss::getType()const{
    return WIZARDBOSS;
}

void WizardBoss::setDead(){
    m_isDead = true;
    setGraphics(ANIMATIONS_POSITIONS::BossDead,1);
    updateSprite();
}

bool WizardBoss::getDead()const{
    return m_isDead;
}

//----------observer functions----------
void WizardBoss::updateLinkPosition(const sf::Vector2f& position){
    m_linkPos = position;
}

void WizardBoss::removeLink()
{
    m_link = nullptr;
}

void WizardBoss::registerAsLinkObserver(Link* link){
    m_link = link;
    m_link->RegisterObserver(this);
    m_linkPos = link->getPosition();
}