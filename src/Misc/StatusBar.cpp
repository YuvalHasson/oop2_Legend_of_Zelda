#include "StatusBar.h"

StatusBar::StatusBar()
	:m_statusBar(sf::Vector2f(WindowWidth * 1.3f, 75.f)), m_hp(0), m_type(NoWeapon) {}

StatusBar::StatusBar(int hp, Weapons type)
	:m_statusBar(sf::Vector2f(WindowWidth * 1.3f, 75.f)), m_hp(hp), m_type(type)
{
	m_statusBar.setFillColor(sf::Color(248, 248, 168));
	m_hpSprite.setTexture(*Resources::getResource().getTexture(TEXTURE::StatusBar));
	m_hpSprite.setScale(3.f, 3.f);

	m_equipped.setTexture(*Resources::getResource().getTexture(TEXTURE::StatusBar));
	m_equipped.setScale(3.f, 3.f);
	sf::IntRect rect(120.f, 210.f, 28.f, tileSize);
	m_equipped.setTextureRect(rect);

	m_weapon.setTexture(*Resources::getResource().getTexture(TEXTURE::StatusBar));
	m_weapon.setScale(3.f, 3.f);

	m_shield.setTexture(*Resources::getResource().getTexture(TEXTURE::StatusBar));
	m_shield.setScale(3.f, 3.f);
	sf::IntRect rect1(48, 41, tileSize / 2.f, tileSize);
	m_shield.setTextureRect(rect1);
	m_shield.setPosition(WindowWidth / 4.f * 1.15f, windowHeight / 9.f * 6.7f);
}

void StatusBar::draw(sf::RenderTarget& target)
{
	target.draw(m_statusBar);

	for (size_t i = 0; i < 2; i++)
	{
		drawEquipped(target, i);
	}

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
		drawHearts(target, { 48, 61 }, offset);
	}
	if (halfHeart == 1)
	{
		drawHearts(target, { 68, 61 }, offset);
	}
	target.draw(m_shield);
}

void StatusBar::drawHearts(sf::RenderTarget& target, const sf::Vector2f& textureRect, const int& offset)
{
	m_hpSprite.setPosition(WindowWidth / 4.f * 3.f, windowHeight / 9.f * 6.9f);
	sf::IntRect rect(textureRect.x, textureRect.y, tileSize / 2.f, tileSize / 2.f);
	m_hpSprite.setTextureRect(rect);
	m_hpSprite.move(offset * 16.f, 0.f);
	target.draw(m_hpSprite);
}

void StatusBar::drawEquipped(sf::RenderTarget& target, const int& offset)
{
	sf::IntRect rect;
	rect.width = tileSize/2.f;
	rect.height = tileSize;
	rect.top = 41;
	switch(m_type){
		case SwordWeapon:
			rect.left = 58;
			break;
		case BowWeapon:
			rect.left = 138;
			break;
		default:
			rect.width = 0;
			rect.height = 0;
			break;
	}
	m_weapon.setTextureRect(rect);
	m_equipped.setPosition(WindowWidth / 4.f * 1.f, windowHeight / 9.f * 6.7f);
	m_weapon.setPosition(WindowWidth / 4.f * 1.9f, windowHeight / 9.f * 6.7f);
	m_equipped.move(offset * 30.f * 5.f, 0.f);
	target.draw(m_equipped);
	target.draw(m_weapon);
}

void StatusBar::setBottomView(const sf::RenderTarget& target)
{
	sf::FloatRect statusBarRect = m_statusBar.getLocalBounds();
	m_statusBar.setPosition(0.f, target.getSize().y - statusBarRect.height);
}

void StatusBar::update(const int& hp, Weapons type)
{
	m_hp = hp;
	m_type = type;
}

