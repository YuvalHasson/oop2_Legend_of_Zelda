#pragma once

#include <SFML/Graphics.hpp>

class LinkObserver{
public:
    virtual ~LinkObserver() = default;
    virtual void updateLinkPosition(const sf::Vector2f& position) = 0;
    virtual void removeLink() = 0;
};