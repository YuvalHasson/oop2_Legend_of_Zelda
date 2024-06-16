#include "Factory.h"

#include "GameObject.h"
#include "Link.h"
#include "Wall.h"
#include "Pot.h"
#include "Enemy.h"
#include "WaterTile.h"
#include "Octorok.h"
#include "Sword.h"

#include <iostream> // debug

std::vector<std::unique_ptr<StaticObjects>> Factory::createStaticObjects(const std::vector<std::pair<std::string, Cell>>& map) {
    std::vector<std::unique_ptr<StaticObjects>> staticObjects;
   
	for (const auto& objMap : map)
	{
		if (objMap.first == "wall" || objMap.first == "house" || objMap.first == "flowers" || objMap.first == "tree")
		{
			auto obj = create("Wall", sf::Vector2f(tileSize * objMap.second.col, tileSize * objMap.second.row));
			if (obj)
			{
				if (auto staticObj = dynamic_cast<StaticObjects*>(obj.get()))
				{
					staticObjects.emplace_back(std::unique_ptr<StaticObjects>(staticObj));
					obj.release();
				}
			}
		}
		else if (objMap.first == "sea")
		{
			auto obj = create("WaterTile", sf::Vector2f(tileSize * objMap.second.col, tileSize * objMap.second.row));
			if (obj)
			{
				if (auto staticObj = dynamic_cast<StaticObjects*>(obj.get()))
				{
					staticObjects.emplace_back(std::unique_ptr<StaticObjects>(staticObj));
					obj.release();
				}
			}
		}
	}
    return staticObjects;
}

std::unique_ptr<Link> Factory::createLink()
{
	std::unique_ptr<Link> linkPtr;
    auto obj = create("Link", { 32.f, 50.f });
    if (obj)
    {
        if (auto link = dynamic_cast<Link*>(obj.get())) {
            linkPtr = std::unique_ptr<Link>(link);
            obj.release();
        }
    }
    return linkPtr;
}

std::vector<std::unique_ptr<Enemy>> Factory::createEnemies()
{
	std::vector<std::unique_ptr<Enemy>> enemies;
	auto obj = create("Octorok", { 32.f, 180.f });
	if (obj)
	{
		if (auto enemy = dynamic_cast<Enemy*>(obj.get()))
		{
			enemies.emplace_back(std::unique_ptr<Enemy>(enemy));
			obj.release();
		}
	}
	return enemies;
}

std::unique_ptr<GameObject> Factory::create(const std::string& name, const sf::Vector2f& position) {
	auto it = getMap().find(name);
	if (it == getMap().end())
	{
		return nullptr;
	}
	return it->second(position);
}

std::unique_ptr<Sword> Factory::createSword() {
	std::unique_ptr<Sword> swordPtr;
    auto obj = create("Sword", {0,0});
    if (obj)
    {
        if (auto sword = dynamic_cast<Sword*>(obj.get())) {
            swordPtr = std::unique_ptr<Sword>(sword);
            obj.release();
        }
    }
    return swordPtr;
}



bool Factory::registerit(const std::string& name, std::unique_ptr<GameObject>(*f)(const sf::Vector2f&))
{
	getMap().emplace(name, f);
	return true;
}