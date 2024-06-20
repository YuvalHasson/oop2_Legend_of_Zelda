#pragma once

#include "Animate/Animate.h"

class Sword : public Animate
{
public:
    Sword(const sf::Texture&, const sf::Vector2f&);

    virtual const sf::Vector2u& getAnimationTexturePosition(Input) { return sf::Vector2u(0, 0); };
    virtual std::unique_ptr<Inanimate> getAttack() { return nullptr; };

    virtual void update(const sf::Time&) override;
    void activate(const sf::Vector2f&, const sf::Vector2i&);
    void deActivate();
    bool getActive()const;
    void setActive(bool);

private:
    bool m_active;
    static bool m_registerit;
};