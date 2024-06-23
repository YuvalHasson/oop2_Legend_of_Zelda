#include "PigWarrior.h"

#include <iostream> // Debug

bool PigWarrior::m_registerit = Factory<PigWarrior>::instance()->registerit("PigWarrior",
    [](const sf::Vector2f& position) -> std::unique_ptr<PigWarrior>
    {
        return std::make_unique<PigWarrior>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

PigWarrior::PigWarrior(const sf::Texture& texture, const sf::Vector2f& position)
    : Enemy(texture, position, sf::Vector2f(10, 10), sf::Vector2f(10 / 2, 10 / 2)), 
        m_moveStrategy(std::make_unique<PatrolMovement>()), m_currInput(PRESS_DOWN), m_sword(),
        m_projectile(nullptr), m_attackStrategy(std::make_unique<Shoot>())
{
    setDirection(DIRECTIONS::Down);
    setGraphics(ANIMATIONS_POSITIONS::PigWarriorDown, 1, false, true);
    updateSprite();
    setHp(2);
}

PigWarrior::~PigWarrior()
{
    if (m_link == nullptr)
    {
        m_link->RemoveObserver(this);
    }
}

void PigWarrior::update(const sf::Time& deltaTime)
{
    setAttackStrategy(std::make_unique<Shoot>());
    sf::Vector2f currentPosition = getSprite().getPosition();
    // If Link is close, change movement strategy
    if (distance(currentPosition, m_linkPos) < 60.0f) {
        // If the distance to the Link is small enough, change strategy  to track Link
        setMoveStrategy(std::make_unique<SmartMovement>());
        //PerformAttack();
    }
    else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        setMoveStrategy(std::make_unique<PatrolMovement>());
        
    }
    PerformMove();

    // Update graphics
    updateGraphics(deltaTime);
    updateSprite();

    if (getHp() <= 0)
    {
        destroy();
    }
}

sf::Vector2f PigWarrior::getLinkPos()
{
    return m_link->getPosition();
}

void PigWarrior::attack()
{
    setAttacking(true);
}

void PigWarrior::draw(sf::RenderTarget& target)
{
    GameObject::draw(target);
    // m_sword->draw(target);
    target.draw(getSprite());
}

const sf::Vector2u& PigWarrior::getAnimationTexturePosition(Input side)
{
    switch (side)
    {
    case PRESS_UP:
        return ANIMATIONS_POSITIONS::PigWarriorUp;
    case PRESS_DOWN:
        return ANIMATIONS_POSITIONS::PigWarriorDown;
    case PRESS_LEFT:
        return ANIMATIONS_POSITIONS::PigWarriorLeft;
    case PRESS_RIGHT:
        return ANIMATIONS_POSITIONS::PigWarriorRight;
    }
}

void PigWarrior::setMoveStrategy(std::unique_ptr<MovementStrategy> move)
{
    m_moveStrategy = std::move(move);
}

void PigWarrior::PerformMove()
{
    m_moveStrategy->move(m_currInput, *this, &m_directionChangeClock);
}

void PigWarrior::setAttackStrategy(std::unique_ptr<AttackStrategy> attack)
{
    m_attackStrategy = std::move(attack);
}

void PigWarrior::PerformAttack()
{
    std::cout << "pigAttack\n";
    m_attackDuration = sf::seconds(0.3f);
    m_attackStrategy->attack(m_attackDuration, m_attackTimer, m_projectile, *this);
    std::cout << "pigAfterAttack\n";
}

void PigWarrior::insertSword(Sword* sword)
{
}

Sword* PigWarrior::getSword()
{
    if (m_attacking) {
        return m_sword.get();
    }
    return nullptr;
}

void PigWarrior::swipeSword()
{
    if (m_sword) 
    {
        m_sword->activate(getSprite().getPosition(), getDirection());
    }
}

void PigWarrior::stopSwordSwipe()
{
    if (m_sword) {
        m_sword->deActivate();
    }
    setAttacking(false);
}

float PigWarrior::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::unique_ptr<Inanimate> PigWarrior::getAttack()
{
    setAttacking(false);
    return std::move(m_projectile);
}

//--------------observer function--------------
void PigWarrior::updateLinkPosition(const sf::Vector2f& position){
    m_linkPos = position;
}

void PigWarrior::registerAsLinkObserver(Link* link){
    m_link = link;
    m_link->RegisterObserver(this);
}