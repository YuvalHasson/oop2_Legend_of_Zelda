#include "Sign.h"

bool Sign::m_registerit = Factory<StaticObjects>::instance()->registerit("Sign",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Sign>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Sign::Sign(const sf::Texture& Texture, const sf::Vector2f& position)
	: InDestructible(Texture, position, sf::Vector2f(tileSize, tileSize + 5), sf::Vector2f(0, 0)), m_active(false),
	m_hitBox(position ,sf::Vector2f(tileSize, tileSize), sf::Vector2f(0,0))
{
	getSprite().setColor(sf::Color::Transparent);
	getSprite().scale(0.7f, 0.7f);
}

void Sign::setActive(bool active)
{
	m_active = active;
}

void Sign::draw(sf::RenderTarget& target)
{
	GameObject::draw(target);
	sf::RectangleShape inner;
	inner.setPosition(m_hitBox.GetRect().left, m_hitBox.GetRect().top);
	inner.setSize(sf::Vector2f(m_hitBox.GetRect().width, m_hitBox.GetRect().height));
	inner.setFillColor(sf::Color::Transparent);
	inner.setOutlineColor(sf::Color::Blue);
	inner.setOutlineThickness(1);
	//target.draw(inner);
	if (m_active)
	{
		sf::RectangleShape rect(sf::Vector2f(32, 32));
		rect.setPosition(getPosition());
		rect.setFillColor(sf::Color::Red);
		target.draw(rect);
	}

}

bool Sign::getInnerBox(const HitBox& box) const
{
	return m_hitBox.checkCollision(box);
}
