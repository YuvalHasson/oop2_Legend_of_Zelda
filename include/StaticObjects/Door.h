#pragma once

#include "InDestructible.h"

class Door : public InDestructible
{
public:
	Door(const sf::Texture&, const sf::Vector2f&);

	void setLevelToDoor(const Level& level);
	Level getLevel() const;
	bool getChangeLevel() const;
	void setChangeLevel(bool);
	void setLinkOutPosition(const sf::Vector2f&);
	sf::Vector2f getLinkOutPosition() const;

private:
	Level m_level;
	bool m_changeLevel;
	sf::Vector2f m_linkOutPosition;
	static bool m_registerit;
};