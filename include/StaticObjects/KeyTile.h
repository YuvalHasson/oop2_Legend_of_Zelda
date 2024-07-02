#pragma once

#include "Inanimate.h"

class KeyTile : public Inanimate
{
public:
	KeyTile(const sf::Texture&, const sf::Vector2f&);
	void update(const sf::Time&) override;
	void updateIsCovered();
	bool isCovered();

private:
	static bool m_registerit;
	bool m_isCovered;
	sf::Clock m_lastTimeOfCover;
};