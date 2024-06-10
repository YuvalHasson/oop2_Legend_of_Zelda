#include "Factory.h"

std::unique_ptr<MovingObjects> Factory::createLink(const sf::Vector2f& position)
{
	return std::make_unique<Link>(*Resources::getResource().getTexture(TEXTURE::Link), position);
}

std::unique_ptr<MovingObjects> Factory::createOctorok(const sf::Vector2f& position)
{
	return std::make_unique<Octorok>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
}

std::unique_ptr<StaticObjects> Factory::createWall(const sf::Vector2f& position)
{
	return std::make_unique<Wall>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
}

std::unique_ptr<StaticObjects> Factory::createPot(const sf::Vector2f& position)
{
	return std::make_unique<Pot>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
}

std::unique_ptr<StaticObjects> Factory::createWaterTile(const sf::Vector2f& position)
{
	return std::make_unique<WaterTile>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
}