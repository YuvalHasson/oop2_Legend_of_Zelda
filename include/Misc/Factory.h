#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "Utilities.h"

class GameObject;
class StaticObjects;
class Enemy;
class Link;
class MovingObjects;
class Sword;
class OctorokProjectile;
class Boulder;


template <typename T>
class Factory
{
public:
	typedef std::map<std::string, std::unique_ptr<T>(*)(const sf::Vector2f&)> mymap;

	//std::vector<std::unique_ptr<StaticObjects>> createStaticObjects(const std::vector<std::pair<std::string, Cell>>&);
	//static std::unique_ptr<Link> createLink();
	//static std::vector<std::unique_ptr<MovingObjects>> createEnemies();
	//static std::unique_ptr<Sword> createSword();
	//static std::unique_ptr<OctorokProjectile> createOctorokProjectile();
	//static std::vector<std::unique_ptr<MovingObjects>> createBoulder();

	std::unique_ptr<T> create(const std::string& name, const sf::Vector2f& position);
	bool registerit(const std::string& name, std::unique_ptr<T>(*)(const sf::Vector2f&));

	static Factory<T>* instance()
	{
		static Factory<T> instance;
		return &instance;
	}

private:
	mymap m_map;
};

template<typename T>
std::unique_ptr<T> Factory<T>::create(const std::string& name, const sf::Vector2f& position)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
	{
		return nullptr;
	}
	return it->second(position);
}

template<typename T>
bool Factory<T>::registerit(const std::string& name, std::unique_ptr<T>(*f)(const sf::Vector2f&))
{
	m_map.emplace(name, f);
	return false;
}


//{
//	char c;
//	if (auto p = Factory<StaticObjects>::instance()->create(c, { 0.f, 0.f }))
//	{
//		m_staticObjects.push_back(std::move(p));
//		continue;
//	}
//	if (auto p = Factory<MovingObjects>::instance()->create(c, { 0.f, 0.f }))
//	{
//		m_movingObjects.push_back(std::move(p));
//		continue;
//	}
//	throw std::runtime_error("Unknown character in map file");
//}