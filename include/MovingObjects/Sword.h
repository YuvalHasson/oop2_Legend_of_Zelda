#pragma once

#include "Inanimate.h"

class Sword : public Inanimate
{
public:
    Sword(const sf::Texture&, const sf::Vector2f&);

    virtual void update(const sf::Time&) override;
    void activate(const sf::Vector2f&, const sf::Vector2i&);
    void deActivate();
    bool getActive() const;
    void setActive(const bool&);

private:
    bool m_active;
    static bool m_registerit;
};