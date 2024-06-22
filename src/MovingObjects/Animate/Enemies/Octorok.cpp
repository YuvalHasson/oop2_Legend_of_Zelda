#include "Octorok.h"

#include <iostream> //debug

bool Octorok::m_registerit = Factory<Octorok>::instance()->registerit("Octorok",
    [](const sf::Vector2f& position) -> std::unique_ptr<Octorok>
    {
        return std::make_unique<Octorok>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	: Enemy(texture, position, sf::Vector2f(12,12), sf::Vector2f(12/2, 12/2)),
    m_state(std::make_unique<OctorokStandingState>()),
    m_projectile(nullptr)
{
    setDirection(DIRECTIONS::Down);
	setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2);
	updateSprite();
    setHp(2);
}


void Octorok::update(const sf::Time& deltaTime)
{ 
    bool up         = false;
    bool down       = false;
    bool right      = false;
    bool left       = false;
    bool standing   = false;
    bool attacking  = false;
    auto directionChange = m_directionChangeClock.getElapsedTime().asSeconds();
    if (directionChange >= 1.0f) // Change direction every 1 seconds
    {
        int randomMovment = rand() % 6;

        switch (randomMovment)
        {
        case 0:
            up = true;
            break;
        case 1:
            down = true;
            break;
        case 2:
            right = true;
            break;
        case 3:
            left = true;
            break;
        case 4:
			attacking = true;
			break;
        default:
            directionChange += 0.5f;
            standing = true;
            break;
        }
        m_directionChangeClock.restart();
    }

    Input input;

    if (up)
    {
        input = PRESS_UP;
    }
    else if (down)
    {
        input = PRESS_DOWN;
    }
    else if (right)
    {
        input = PRESS_RIGHT;
    }
    else if (left)
    {
        input = PRESS_LEFT;
    }
    else if (standing)
    {
        input = STANDING;
    }
    else if (attacking)
	{
		input = PRESS_SPACE;
	}
    else
    {
        input = NONE;
    }

    std::unique_ptr<OctorokState> state = m_state->handleInput(input);

    if (state) {
        m_state = std::move(state);
        m_state->enter(*this);

        updateGraphics(deltaTime);
    }
    updateSprite();

    if(getHp() <= 0)
    {
        destroy();
    }
}

void Octorok::attack()
{
	setAttacking(true);
}

const sf::Vector2u& Octorok::getAnimationTexturePosition(Input side)
{
    switch (side)
    {
    case PRESS_UP:
        return ANIMATIONS_POSITIONS::OctorokDown;
    case PRESS_DOWN:
        return ANIMATIONS_POSITIONS::OctorokDown;
    case PRESS_LEFT:
        return ANIMATIONS_POSITIONS::OctorokLeft;
    case PRESS_RIGHT:
        return ANIMATIONS_POSITIONS::OctorokRight;
    }
}

std::unique_ptr<Inanimate> Octorok::getAttack()
{
    if(m_attacking)
    {
        if (auto p = Factory<OctorokProjectile>::instance()->create("OctorokProjectile", getPosition()))
        {
            m_projectile = std::move(p);

            m_projectile->setDirection(getDirection());
        }
        setAttacking(false);
        return std::move(m_projectile);
    }
    return nullptr;
}