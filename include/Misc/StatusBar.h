#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class StatusBar
{
public:
	StatusBar();
	StatusBar(int, bool);
	~StatusBar() = default;

	void draw(sf::RenderTarget&);

	void setBottomView(const sf::RenderTarget&);

	void update(const int&, const bool&);

private:
	void drawHearts(sf::RenderTarget&, const sf::Vector2f&, const int&);
	void drawEquipped(sf::RenderTarget&, const int&);
	int m_hp;
	bool m_type; // false for sword, true for arrow // mabye change for enum

	sf::RectangleShape m_statusBar;

	sf::Sprite m_hpSprite;
	sf::Sprite m_equipped; //for what weapond is now on
	sf::Sprite m_weapon; //for the sprite to draw
};