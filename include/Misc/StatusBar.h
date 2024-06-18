#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class StatusBar
{
public:
	StatusBar(int);
	~StatusBar() = default;

	void draw(sf::RenderTarget&);

	void setBottomView(const sf::RenderTarget&);
	sf::Vector2f getSize() const { return m_statusBar.getSize(); }

	void update(int hp);

private:
	void drawHearts(sf::RenderTarget&, const sf::Vector2f&, int);

	sf::RectangleShape m_statusBar;

	int m_hp;

	sf::Sprite m_hpSprite;
};