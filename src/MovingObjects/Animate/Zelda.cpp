#include "Zelda.h"

bool Zelda::m_registerit = Factory<Zelda>::instance()->registerit("Zelda",
	[](const sf::Vector2f& position) -> std::unique_ptr<Zelda>
	{
		return std::make_unique<Zelda>(*Resources::getResource().getTexture(TEXTURE::Zelda), position);
	});

Zelda::Zelda(const sf::Texture& texture, const sf::Vector2f& position)
	:Animate(texture, position, sf::Vector2f(7.f + 4, 7.5f), sf::Vector2f(tileSize / 4.5f, tileSize / 9.f)),
	m_hitBox(position, sf::Vector2f(tileSize / 4.5f, tileSize / 9.f), sf::Vector2f(0, 0)), m_active(false)
{
	m_text.setFont(*Resources::getResource().getFont());
	m_text.scale(0.9f, 0.9f);
	m_text.setLineSpacing(1.6f);
	m_text.setLetterSpacing(2.f);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("Go  kill  the  wizard");

	getSprite().setOrigin(tileSize, tileSize);
	setGraphics({1, 11}, 1);
	updateSprite();
}

std::unique_ptr<Inanimate> Zelda::getAttack()
{
	return nullptr;
}

void Zelda::setActive(bool active)
{
	m_active = active;
}

void Zelda::draw(sf::RenderTarget& target)
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

bool Zelda::getInnerBox(const HitBox& box) const
{
	return m_hitBox.checkCollision(box);
}
