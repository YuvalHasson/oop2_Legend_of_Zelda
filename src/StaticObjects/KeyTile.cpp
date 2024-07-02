#include "KeyTile.h"

#include <iostream> //debugging

bool KeyTile::m_registerit = Factory<Inanimate>::instance()->registerit("KeyTile",
	[](const sf::Vector2f& position) -> std::unique_ptr<Inanimate>
	{
		return std::make_unique<KeyTile>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

KeyTile::KeyTile(const sf::Texture& texture, const sf::Vector2f& position)
	: Inanimate(texture, position, sf::Vector2f(tileSize/4, tileSize/4), sf::Vector2f(-6.f, -6.f)),
	 m_isCovered(false)
{
	getSprite().setColor(sf::Color::Transparent);
	getSprite().scale(0.7f, 0.7f);
}

void KeyTile::update(const sf::Time&)
{
	if (m_lastTimeOfCover.getElapsedTime().asSeconds() > 0.5f)
	{
		m_isCovered = false;
	}
}

void KeyTile::updateIsCovered()
{
	m_lastTimeOfCover.restart();
	m_isCovered = true;
}

bool KeyTile::isCovered()
{
	return m_isCovered;
}
