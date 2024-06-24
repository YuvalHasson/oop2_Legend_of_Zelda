#pragma once

#include <SFML/Graphics.hpp>

class LinkObserver{
public:
    virtual void updateLinkPosition(const sf::Vector2f& position) = 0;
    virtual void removeLink() = 0;
};