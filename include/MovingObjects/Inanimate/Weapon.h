#pragma once

#include "Inanimate.h"

class Weapon : public Inanimate 
{
public:
    Weapon(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
    virtual void update(const sf::Time&) = 0;
    virtual void setBool() = 0;
};