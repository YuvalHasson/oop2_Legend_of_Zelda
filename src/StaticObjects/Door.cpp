#include "Door.h"

bool Door::m_registerit = Factory<Door>::instance()->registerit("Door",
	[](const sf::Vector2f& position) -> std::unique_ptr<Door>
	{
		return std::make_unique<Door>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Door::Door(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position, { tileSize, tileSize }, { 0.f, 0.f }),
	m_changeLevel(false), m_victoryDoor(false)
{
	getSprite().setColor(sf::Color::Transparent);
}

void Door::setLevelToDoor(const Level& level)
{
	m_level = level;
}

Level Door::getLevel() const
{
	return m_level;
}

bool Door::getChangeLevel() const
{
	return m_changeLevel;
}

void Door::setChangeLevel(bool change)
{
	m_changeLevel = change;
}

void Door::setLinkOutPosition(const sf::Vector2f& position)
{
	m_linkOutPosition = position;
}

sf::Vector2f Door::getLinkOutPosition() const
{
	return m_linkOutPosition;
}

void Door::setVictoryDoor(bool victory)
{
	m_victoryDoor = victory;
}

bool Door::getVictoryDoor() const
{
	return m_victoryDoor;
}
