#include "StatusBar.h"

StatusBar::StatusBar(int hp)
	:m_statusBar(sf::Vector2f(WindowWidth * 1.3f, 75.f)), m_hp(hp)
{
	m_statusBar.setFillColor(sf::Color(248, 248, 168));
	m_hpSprite.setTexture(*Resources::getResource().getTexture(TEXTURE::StatusBar));
	m_hpSprite.setScale(3.f, 3.f);

}

void StatusBar::draw(sf::RenderWindow& window)
{
	window.draw(m_statusBar);
	int fullHeart = 0, halfHeart = 0;
	if (m_hp % 2 == 0)
	{
		fullHeart = m_hp / 2;
	}
	else
	{
		fullHeart = m_hp / 2;
		halfHeart = 1;
	}
	int offset = 0;
	for (; offset < fullHeart; offset++)
	{
		drawHearts(window, { 48, 61 }, offset);
	}
	if (halfHeart == 1)
	{
		drawHearts(window, { 68, 61 }, offset);
	}
}

void StatusBar::drawHearts(sf::RenderWindow& window, const sf::Vector2f& textureRect, int offset)
{
	m_hpSprite.setPosition(WindowWidth / 4.f * 3.f, windowHeight / 9.f * 6.9f);
	sf::IntRect rect(textureRect.x, textureRect.y, tileSize / 2.f, tileSize / 2.f);
	m_hpSprite.setTextureRect(rect);
	m_hpSprite.move(offset * 15.f, 0.f);
	window.draw(m_hpSprite);
}

void StatusBar::setBottomView(const sf::RenderWindow& window)
{
	sf::FloatRect statusBarRect = m_statusBar.getLocalBounds();
	m_statusBar.setPosition(0.f, window.getSize().y - statusBarRect.height);
}

void StatusBar::update(int hp)
{
	m_hp = hp;
}
