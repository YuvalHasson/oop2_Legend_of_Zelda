#include "MainMenu.h"
#include "NewGameState.h"

#include <iostream> // std::cout

MainMenu::MainMenu(sf::RenderWindow* window)
	:State(window)
{
	m_menuBackground.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_menuBackground.setTexture(Resources::getResource().getTexture(TEXTURE::Menu));

	add("Start", std::make_unique<StartButton>(this));
	add("Exit", std::make_unique<ExitButton>(this));
	add("Settings", std::make_unique<SettingsButton>(this));
	add("Help", std::make_unique<HelpButton>(this));
	add("Load", std::make_unique<LoadButton>(this));
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

void MainMenu::overButton(sf::RenderWindow& window)
{
	for (auto& option : m_options)
	{
		option.second->overButton(window);
	}
}

void MainMenu::startGame()
{
	updateState(GAME_STATE::NEW_GAME);
	std::cout << getGameState() << std::endl;
}

void MainMenu::exitGame()
{
	updateState(GAME_STATE::EXIT);
}

void MainMenu::update(const sf::Time&)
{
	overButton(*getWindow());
}

void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	drawMainMenu(*getWindow());
}

std::unique_ptr<State> MainMenu::handleInput(GAME_STATE gameState)
{
	if (getGameState() == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (getGameState() == GAME_STATE::NEW_GAME)
	{
		return std::make_unique<NewGameState>(getWindow());
	}
	else if (getGameState() == GAME_STATE::EXIT)
	{
		getWindow()->close();
		return nullptr;
	}
	return std::make_unique<MainMenu>(getWindow());
}

void MainMenu::add(const std::string& name, std::unique_ptr<Button> c)
{
	m_options.emplace_back(Option(name, std::move(c)));
}
