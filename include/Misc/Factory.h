#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "Utilities.h"

template <typename T>
class Factory
{
public:
	typedef std::map<std::string, std::unique_ptr<T>(*)(const sf::Vector2f&)> mymap;

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