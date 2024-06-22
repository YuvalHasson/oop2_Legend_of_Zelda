#include "PigWarrior.h"

#include <iostream> // Debug

bool PigWarrior::m_registerit = Factory<MovingObjects>::instance()->registerit("PigWarrior",
    [](const sf::Vector2f& position) -> std::unique_ptr<MovingObjects>
    {
        return std::make_unique<PigWarrior>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

PigWarrior::PigWarrior(const sf::Texture& texture, const sf::Vector2f& position)
    : Enemy(texture, position, sf::Vector2f(10, 10), sf::Vector2f(tileSize / 2, tileSize / 2)), 
       m_currInput(PRESS_UP), m_sword(), m_moveStrategy(std::make_unique<PatrolMovement>())
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
        setMoveStrategy(std::make_unique<SmartMovement>());
    }
    else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 2.0f)
    {
        //std::cout << m_directionChangeClock.getElapsedTime().asSeconds() << "\n";
        setMoveStrategy(std::make_unique<PatrolMovement>());
        //m_directionChangeClock.restart();
    }
    PerformMove();
  /*  else if (m_directionChangeClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        std::cout << "pig attack\n" << "\n";
        std::unique_ptr <MovementStrategy> newMove = std::make_unique<AttackingState>();
        setMoveStrategy(newMove);*/
    //}

    //m_moveStrategy->enter(*this);
    //m_sword->update(deltaTime);

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

void PigWarrior::draw(sf::RenderTarget& target)
{
    //m_sword->draw(target);
    target.draw(getSprite());

    //draw hitbox for debugging
    sf::RectangleShape rect;
    rect.setPosition(getHitBox().GetRect().left, getHitBox().GetRect().top);
    rect.setSize(sf::Vector2f(getHitBox().GetRect().width, getHitBox().GetRect().height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(1);
    target.draw(rect);
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
    m_moveStrategy->move(m_currInput, *this, m_link, &m_directionChangeClock);
}

void PigWarrior::UpdateLinkPos(const sf::Vector2f& position)
{
    m_linkPos = position;
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
    //std::cout << "in attack state\n";
    if (m_sword) 
    {
        std::cout << "in m_sword\n";
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
