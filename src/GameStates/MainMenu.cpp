#include "MainMenu.h"

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


void MainMenu::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
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

void MainMenu::update(const sf::Time&)
{
	overButton(*getWindow());
}

void MainMenu::render(sf::RenderTarget* target)
{
	getWindow()->setView(getWindow()->getDefaultView());
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_menuBackground);
	for (auto& option : m_options)
	{
		option.second->draw(*target);
	}
}

std::unique_ptr<State> MainMenu::handleInput(const GAME_STATE& gameState)
{
	switch (gameState)
	{
	case  GAME_STATE::NEW_GAME:
		SoundResource::getSound().stopBackground(BACKGROUND_SOUND::Menu);
		return std::make_unique<NewGameState>(getWindow());
		break;
	case  GAME_STATE::SETTINGS:
		return std::make_unique<SettingState>(getWindow());
		break;
	case  GAME_STATE::HELP:
		return std::make_unique<HelpState>(getWindow());
		break;
	//case  GAME_STATE::LOAD:	
		//return std::make_unique<LoadState>(getWindow());
		//	break;
	case  GAME_STATE::EXIT:
		getWindow()->close();
		break;
	}
	return nullptr;
}

void MainMenu::add(const std::string& name, std::unique_ptr<Button> c)
{
	m_options.emplace_back(Option(name, std::move(c)));
}
