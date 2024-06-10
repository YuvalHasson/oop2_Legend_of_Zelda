#pragma once

#include <memory>

#include "GameObject.h"
#include "Resources.h"
#include "Link.h"
#include "Wall.h"
#include "Pot.h"
#include "WaterTile.h"
#include "Octorok.h"


class Factory
{
public:
    static std::unique_ptr<MovingObjects> createLink(const sf::Vector2f& position);
	static std::unique_ptr<MovingObjects> createOctorok(const sf::Vector2f& position);
    static std::unique_ptr<StaticObjects> createWall(const sf::Vector2f& position);
	static std::unique_ptr<StaticObjects> createPot(const sf::Vector2f& position);
	static std::unique_ptr<StaticObjects> createWaterTile(const sf::Vector2f& position);
};