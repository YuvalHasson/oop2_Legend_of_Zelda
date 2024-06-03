#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_menuBackground.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_menuBackground.setTexture(Resources::getResource().getTexture(TEXTURE::Menu));

	//m_Button.createButton(sf::Vector2f(60, 450), sf::Vector2f(200, 50));
	m_Button.setText("Start", sf::Vector2f(70, 485));
	
}

void MainMenu::drawMainMenu(sf::RenderWindow& window)
{
	window.draw(m_menuBackground);
	m_Button.draw(window);
}

int MainMenu::buttonPressed(sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event)
{
	if (m_Button.isButtonPressed(window, event))
	{
		return GAME_STATE::NEW_GAME;
	}
	return GAME_STATE::MAIN_MENU;
}