#include "MainMenu.h"

#include <iostream> // std::cout

MainMenu::MainMenu()
	: m_gameState(GAME_STATE::MAIN_MENU)
{
	m_menuBackground.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_menuBackground.setTexture(Resources::getResource().getTexture(TEXTURE::Menu));

	add("Start", std::make_unique<StartButton>(this));
}

void MainMenu::drawMainMenu(sf::RenderWindow& window)
{
	window.draw(m_menuBackground);
	
	for (auto& option : m_options)
	{
		option.second->draw(window);
	}
}

void MainMenu::buttonPressed(sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event))
		{
			option.second->execute();
		}
	}
}

void MainMenu::startGame()
{
	m_gameState = GAME_STATE::NEW_GAME;
}

int MainMenu::getGameState() const
{
	return m_gameState;
}

void MainMenu::add(const std::string& name, std::unique_ptr<Button> c)
{
	m_options.emplace_back(Option(name, std::move(c)));
}
