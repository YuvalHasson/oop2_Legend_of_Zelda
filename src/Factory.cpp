#include "Factory.h"

std::unique_ptr<GameObject> Factory::createObject(const Cell& type, int texture, const sf::Vector2f& position)
{
	switch (type)
	{
	case Cell::Link:
		return std::make_unique<Link>(*Resources::getResource().getResource().getTexture(texture), position);
	case Cell::Wall:
		return std::make_unique<Wall>(*Resources::getResource().getResource().getTexture(texture), position);
	case Cell::Pot:
		return std::make_unique<Pot>(*Resources::getResource().getResource().getTexture(texture), position);
	case Cell::WaterTile:
		return std::make_unique<WaterTile>(*Resources::getResource().getResource().getTexture(texture), position);
	default:
		return nullptr;
	}
}
