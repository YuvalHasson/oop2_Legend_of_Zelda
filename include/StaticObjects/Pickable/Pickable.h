#pragma once

#include "StaticObjects.h"

class Pickable: public StaticObjects{
public:
    Pickable(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

};