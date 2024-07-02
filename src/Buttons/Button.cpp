#include "Button.h"
#include "State.h"

Button::Button()
	: m_state(nullptr) {}

void Button::draw(sf::RenderTarget& target) const
{
	target.draw(m_text);
}

void Button::setState(State* state)
{
	m_state = state;
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_text.setPosition(position);
}

void Button::setText(std::string text, sf::Vector2f position)
{
	m_text.setFont(*Resources::getResource().getFont());
	m_text.setString(text);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(position);
}

void Button::overButton(sf::RenderWindow& window)
{
	sf::Vector2i mouseLoc = sf::Mouse::getPosition(window);
	if (m_text.getGlobalBounds().contains(static_cast<float>(mouseLoc.x), static_cast<float>(mouseLoc.y)))
	{
		m_text.setOutlineColor(sf::Color::White);
		m_text.setOutlineThickness(2);
	}
	else
	{
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(0);
	}
}

bool Button::isButtonPressed(sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event)
{
	return m_text.getGlobalBounds().contains(window.mapPixelToCoords({ event.x, event.y }));
}

State* Button::getState() const
{
	return m_state;
}
