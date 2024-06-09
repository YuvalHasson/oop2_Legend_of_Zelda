#include "Button.h"

Button::Button()
	: m_mainMenu(nullptr)
{
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_text);
}

void Button::setMainMenu(MainMenu* mainMenu)
{
	m_mainMenu = mainMenu;
}

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

MainMenu* Button::getMainMenu() const
{
	return m_mainMenu;
}
