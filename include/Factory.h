#pragma once

#include <memory>

#include "GameObject.h"
#include "Resources.h"
#include "Link.h"
#include "Wall.h"
#include "Pot.h"
#include "WaterTile.h"

class Factory
{
public:
    static std::unique_ptr<GameObject> createObject(const Cell& type, int texture, const sf::Vector2f& position);
};