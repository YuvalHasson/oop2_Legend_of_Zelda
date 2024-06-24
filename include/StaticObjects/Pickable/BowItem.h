#pragma once 

#include "Pickable.h"

class BowItem: public Pickable{
public:
    BowItem(const sf::Texture&, const sf::Vector2f&);

private:
    static bool m_registerit;

};