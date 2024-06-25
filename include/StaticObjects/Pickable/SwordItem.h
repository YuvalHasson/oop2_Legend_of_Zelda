#pragma once 

#include "Pickable.h"

class SwordItem: public Pickable{
public:
    SwordItem(const sf::Texture&, const sf::Vector2f&);

private:
    static bool m_registerit;

};