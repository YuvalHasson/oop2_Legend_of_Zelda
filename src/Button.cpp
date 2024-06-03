#include "Button.h"

Button::Button()
{
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_button);
	window.draw(m_text);
}

//void Button::createButton(sf::Vector2f position, sf::Vector2f size)
//{
//	m_button.setSize(size);
//	m_button.setPosition(position);
//	m_button.setTexture(Resources::getResource().getTexture(TEXTURE::Button));
//}

void Button::setText(std::string text, sf::Vector2f position)
{
	m_text.setFont(*Resources::getResource().getFont());
	m_text.setString(text);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(position);
}

bool Button::isButtonPressed(sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event)
{
	return m_text.getGlobalBounds().contains(window.mapPixelToCoords({ event.x, event.y }));
}
