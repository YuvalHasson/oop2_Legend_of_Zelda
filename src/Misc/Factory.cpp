//#include "Factory.h"
//
//#include "GameObject.h"
//#include "Link.h"
//#include "Wall.h"
//#include "Pot.h"
//#include "Enemy.h"
//#include "WaterTile.h"
//#include "Octorok.h"
//#include "PigWarrior.h"
//#include "Sword.h"
//#include "OctorokProjectile.h"
//#include "Boulder.h"
//
//#include <iostream> // debug

//std::vector<std::unique_ptr<StaticObjects>> Factory::createStaticObjects(const std::vector<std::pair<std::string, Cell>>& map) {
//    std::vector<std::unique_ptr<StaticObjects>> staticObjects;
//   
//	for (const auto& objMap : map)
//	{
//		if (objMap.first == "wall" || objMap.first == "house" || objMap.first == "flowers" || objMap.first == "tree")
//		{
//			auto obj = create("Wall", sf::Vector2f(tileSize * objMap.second.col, tileSize * objMap.second.row));
//			if (obj)
//			{
//				if (auto staticObj = dynamic_cast<StaticObjects*>(obj.get()))
//				{
//					staticObjects.emplace_back(std::unique_ptr<StaticObjects>(staticObj));
//					obj.release();
//				}
//			}
//		}
//		else if (objMap.first == "sea")
//		{
//			auto obj = create("WaterTile", sf::Vector2f(tileSize * objMap.second.col, tileSize * objMap.second.row));
//			if (obj)
//			{
//				if (auto staticObj = dynamic_cast<StaticObjects*>(obj.get()))
//				{
//					staticObjects.emplace_back(std::unique_ptr<StaticObjects>(staticObj));
//					obj.release();
//				}
//			}
//		}
//	}
//
//	auto obj = create("Pot", { 110.f, 100.f });
//	if (obj)
//	{
//		if (auto pot = dynamic_cast<StaticObjects*>(obj.get()))
//		{
//			staticObjects.emplace_back(std::unique_ptr<StaticObjects>(pot));
//			obj.release();
//		}
//	}
//
//    return staticObjects;
//}
//
//std::unique_ptr<Link> Factory::createLink()
//{
//	std::unique_ptr<Link> linkPtr;
//    auto obj = create("Link", { 32.f, 50.f });
//    if (obj)
//    {
//        if (auto link = dynamic_cast<Link*>(obj.get())) {
//            linkPtr = std::unique_ptr<Link>(link);
//            obj.release();
//        }
//    }
//    return linkPtr;
//}
//
//std::vector<std::unique_ptr<MovingObjects>> Factory::createEnemies()
//{
//	std::vector<std::unique_ptr<MovingObjects>> enemies;
//	auto obj = create("Octorok", { 32.f, 180.f });
//	if (obj)
//	{
//		if (auto enemy = dynamic_cast<Enemy*>(obj.get()))
//		{
//			enemies.emplace_back(std::unique_ptr<MovingObjects>(enemy));
//			obj.release();
//		}
//	}
//	auto obj2 = create("PigWarrior", { 80.f, 70.f });
//	if (obj2)
//	{
//		if (auto enemy2 = dynamic_cast<Enemy*>(obj2.get()))
//		{
//			enemies.emplace_back(std::unique_ptr<Enemy>(enemy2));
//			obj2.release();
//
//		}
//	}
//
//	return enemies;
//}
//
//std::unique_ptr<Sword> Factory::createSword()
//{
//	std::unique_ptr<Sword> swordPtr;
//    auto obj = create("Sword", {0,0});
//    if (obj)
//    {
//        if (auto sword = dynamic_cast<Sword*>(obj.get())) {
//            swordPtr = std::unique_ptr<Sword>(sword);
//            obj.release();
//        }
//    }
//    return swordPtr;
//}
//
//std::unique_ptr<OctorokProjectile> Factory::createOctorokProjectile()
//{
//	std::unique_ptr<OctorokProjectile> projectilePtr;
//	auto obj = create("OctorokProjectile", { 0,0 });
//	if (obj)
//	{
//		if (auto projectile = dynamic_cast<OctorokProjectile*>(obj.get()))
//		{
//			projectilePtr = std::unique_ptr<OctorokProjectile>(projectile);
//			obj.release();
//		}
//	}
//	return projectilePtr;
//}
//
//std::vector<std::unique_ptr<MovingObjects>> Factory::createBoulder()
//{
//	std::vector<std::unique_ptr<MovingObjects>> boulderPtr;
//	auto obj = create("Boulder", { 30.f, 30.f });
//	if (obj)
//	{
//		if (auto boulder = dynamic_cast<Boulder*>(obj.get()))
//		{
//			boulderPtr.emplace_back(std::unique_ptr<Boulder>(boulder));
//			obj.release();
//		}
//	}
//	return boulderPtr;
//}

//template <typename T>
//typename Factory<T>::mymap Factory<T>::m_map;
//
//template<typename T>
//std::unique_ptr<T> Factory<T>::create(const std::string& name, const sf::Vector2f& position) {
//	auto it = m_map.find(name);
//	if (it == m_map.end())
//	{
//		return nullptr;
//	}
//	return it->second(position);
//}
//
//template<typename T>
//bool Factory<T>::registerit(const std::string& name, std::unique_ptr<T>(*f)(const sf::Vector2f&))
//{
//	m_map.emplace(name, f);
//	return false;
//}
