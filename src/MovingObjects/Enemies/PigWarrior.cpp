#include "PigWarrior.h"

#include <iostream> // Debug


bool PigWarrior::m_registerit = Factory::registerit("PigWarrior",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<PigWarrior>(*Resources::getResource().getTexture(TEXTURE::Enemies), position); });

PigWarrior::PigWarrior(const sf::Texture& texture, const sf::Vector2f& position)
    : Enemy(texture, position, sf::Vector2f(14, 14), sf::Vector2f(tileSize / 2, tileSize / 2)), m_moveStrategy(std::make_unique<StandingState>()), m_currInput(PRESS_UP), m_sword(nullptr)
{
    setDirection(DIRECTIONS::Down);
    setGraphics(ANIMATIONS_POSITIONS::PigWarriorDown, 1, false, true);
    updateSprite();
    setHp(2);
}

void PigWarrior::update(const sf::Time& deltaTime)
{
    sf::Vector2f currentPosition = getSprite().getPosition();
    // If Link is close, change movement strategy
    if (distance(currentPosition, m_linkPos) < 100.0f) {
        // If the distance to the Link is small enough, change strategy  to track Link
        std::unique_ptr<MovementStrategy> newMove = std::make_unique<SmartMovement>(PRESS_UP, *this, m_linkPos);
        setMoveStrategy(newMove);
        //m_moveStrategy->enter(*this);
    }
    else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 2.0f)
    {
        //std::cout << m_directionChangeClock.getElapsedTime().asSeconds() << "\n";
        std::unique_ptr <MovementStrategy> newMove = std::make_unique<PatrolMovement>(m_currInput, &m_directionChangeClock);
        setMoveStrategy(newMove);
        //m_moveStrategy->enter(*this);
        m_directionChangeClock.restart();
    }
    else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        std::cout << "pig attack\n" << "\n";
        std::unique_ptr <MovementStrategy> newMove = std::make_unique<AttackingState>();
        setMoveStrategy(newMove);
    }

    m_moveStrategy->enter(*this);

    // Update graphics
    updateGraphics(deltaTime);
    updateSprite();

    if (getHp() <= 0)
    {
        destroy();
    }
}

void PigWarrior::handleCollision()
{
    // Implement collision handling if necessary
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

void PigWarrior::setMoveStrategy(std::unique_ptr<MovementStrategy>& move)
{
    m_moveStrategy = std::move(move);
}

void PigWarrior::UpdateLinkPos(const sf::Vector2f& position)
{
    m_linkPos = position;
}
void PigWarrior::insertSword(Sword* sword)
{
    m_sword = sword;
}

void PigWarrior::swipeSword()
{
    std::cout << "in attack state\n";
    if (m_sword) 
    {
        std::cout << "in m_sword\n";
        m_sword->activate(getSprite().getPosition(), getDirection());
    }
}

void PigWarrior::stopSwordSwipe()
{
    if (m_sword) 
    {
        m_sword->deActivate();
    }
}

bool PigWarrior::getInvincible() const
{
    return m_invincibleTimer.getElapsedTime().asSeconds() - invincibilityTime.asSeconds() <= 0;
}

void PigWarrior::initializeInvincible()
{
    m_invincibleTimer.restart();
}

float PigWarrior::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::unique_ptr<MovingObjects> PigWarrior::getAttack()
{
    return std::unique_ptr<MovingObjects>();
}
