#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class StatusBar
{
public:
	StatusBar();
	StatusBar(int, Weapons);
	~StatusBar() = default;

	void draw(sf::RenderTarget&);

	void setBottomView(const sf::RenderTarget&);

	void update(const int&, Weapons);

private:
	void drawHearts(sf::RenderTarget&, const sf::Vector2i&, const int&);
	void drawEquipped(sf::RenderTarget&, const int&);
	int m_hp;
	Weapons m_type;

	sf::RectangleShape m_statusBar;

	sf::Sprite m_hpSprite;
	sf::Sprite m_equipped; //for what weapon is now on
	sf::Sprite m_weapon; //for the sprite to draw
	sf::Sprite m_shield;
};