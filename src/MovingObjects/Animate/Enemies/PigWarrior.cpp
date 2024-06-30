#include "PigWarrior.h"

#include <iostream> // Debug

bool PigWarrior::m_registerit = Factory<Enemy>::instance()->registerit("PigWarrior",
    [](const sf::Vector2f& position) -> std::unique_ptr<Enemy>
    {
        return std::make_unique<PigWarrior>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

PigWarrior::PigWarrior(const sf::Texture& texture, const sf::Vector2f& position)
    :Enemy(texture, position, sf::Vector2f(12.f * 0.8f, 12.f * 0.8f), sf::Vector2f(-2, -2)),
     m_sword(nullptr),
     m_currInput(PRESS_RIGHT),
     m_moveStrategy(std::make_unique<PatrolMovement>()), 
    m_attackStrategy(std::make_unique<Stab>()), m_lineOfSight(position, sf::Vector2f(60.f, 16.f), sf::Vector2f(0, 0))
{
    setDirection(DIRECTIONS::Down);
    setGraphics(ANIMATIONS_POSITIONS::PigWarriorDown, 1, false, true);
    updateSprite();
    setHp(2);
    //m_lineOfSight.setPosition(position);
}

PigWarrior::~PigWarrior()
{
    if (m_link)
    {
        m_link->RemoveObserver(this);
    }
}

void PigWarrior::update(const sf::Time& deltaTime)
{
    bool standing = false;
    bool attacking = false;
    sf::Vector2f currentPosition = getSprite().getPosition();
    // If Link is close, change movement strategy
    if (distance(currentPosition, m_linkPos) < 60.0f) {
        // If the distance to the Link is small enough, change strategy  to track Link
        setMoveStrategy(std::make_unique<SmartMovement>());
        if (distance(currentPosition, m_linkPos) < 16.0f) {
            // If the distance to the Link is small enough, change strategy  to track Link
            PerformAttack();
            m_sword->setBool();
        }
    }
    else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        setMoveStrategy(std::make_unique<PatrolMovement>());
        int randomMovment = rand() % 4;

        switch (randomMovment)
        {
        case 3:
            setMoveStrategy(std::make_unique<Standing>());
            PerformAttack();
            break;
        default:
            break;
        }        
    }
    m_lineOfSight.setPosition(getSprite().getPosition());
    PerformMove();
    updateGraphics(deltaTime);
    updateSprite();
    if (getHp() <= MIN_HEALTH)
    {
        destroy();
    }
	setSpeed(1.f);
}

sf::Vector2f PigWarrior::getLinkPos()
{
    return m_link->getPosition();
}

void PigWarrior::attack()
{
    setAttacking(true);
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
    m_attackDuration = sf::seconds(0.3f);
    m_attackStrategy->attack(m_attackDuration, m_attackTimer, m_sword, *this);
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
    return std::move(m_sword);
}

//void PigWarrior::updateLineOfSight()
//{
//    switch (m_currInput)
//    {
//    case PRESS_UP:
//        m_lineOfSight.setBox(sf::Vector2f(60.f, -60.f), sf::Vector2f(26, 0));
//        break;
//    case PRESS_DOWN:
//        m_lineOfSight.setBox(sf::Vector2f(60.f, 60.f), sf::Vector2f(26, -12));
//        break;
//    case PRESS_LEFT:
//        m_lineOfSight.setBox(sf::Vector2f(-60.f, 60.f), sf::Vector2f(0, 25));
//        break;
//    case PRESS_RIGHT:
//        m_lineOfSight.setBox(sf::Vector2f(60.f, 60.f), sf::Vector2f(-12, 25));
//        break;
//    default:
//        break;
//    }
//    //for (/*loop on the static vetor*/)
//    //{
//    //    if (m_lineOfSight.checkCollision(/*stactic obj*/))
//    //    {
//    //        setMoveStrategy(std::make_unique<PatrolMovement>());
//    //        break;
//    //    }
//
//    //}
//    
//}

//--------------observer function--------------
void PigWarrior::updateLinkPosition(const sf::Vector2f& position){
    m_linkPos = position;
}

void PigWarrior::removeLink()
{
    m_link = nullptr;
}

void PigWarrior::registerAsLinkObserver(Link* link){
    m_link = link;
    m_link->RegisterObserver(this);
}