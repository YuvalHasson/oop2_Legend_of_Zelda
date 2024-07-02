#include "Sign.h"

bool Sign::m_registerit = Factory<Sign>::instance()->registerit("Sign",
	[](const sf::Vector2f& position) -> std::unique_ptr<Sign>
	{
		return std::make_unique<Sign>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position);
	});

Sign::Sign(const sf::Texture& Texture, const sf::Vector2f& position)
	: InDestructible(Texture, position, sf::Vector2f(tileSize + 1, tileSize + 5), sf::Vector2f(0, 0)), m_active(false),
	m_hitBox(position ,sf::Vector2f(tileSize, tileSize), sf::Vector2f(0,0))
{
	m_text.setFont(*Resources::getResource().getFont());
	m_text.scale(0.9f, 0.9f);
	m_text.setLineSpacing(1.6f);
	m_text.setLetterSpacing(2.f);
	m_text.setFillColor(sf::Color::White);

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

	auto curr = target.getView();
	target.setView(target.getDefaultView());


	if (m_active)
	{
		sf::RectangleShape rect(sf::Vector2f(WindowWidth * 1.3f, tileSize * 6.f));
		rect.setPosition(0, windowHeight / 1.57f);
		rect.setOrigin(tileSize / 2.f, tileSize / 2.f);
		rect.setFillColor(sf::Color(0, 0, 0, 200));
		target.draw(rect);

		m_text.setPosition(20.f, rect.getPosition().y - 5.f);
		target.draw(m_text);
	}
	m_active = false;
	target.setView(curr);
}

bool Sign::getInnerBox(const HitBox& box) const
{
	return m_hitBox.checkCollision(box);
}

void Sign::setText(const std::string& text)
{
	m_text.setString(text);
}
