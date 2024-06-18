#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow* window)
	: State(window)
{
}

void GameOverState::update(const sf::Time&)
{
}

void GameOverState::render(sf::RenderTarget* target)
{
	//add background image of game over
	if (!target)
	{
		target = getWindow();
	}
	for (auto& option : m_options)
	{
		option.second->draw(window);
	}
}

std::unique_ptr<State> GameOverState::handleInput(GAME_STATE)
{
	return nullptr;
}

void GameOverState::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}
}

void GameOverState::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.emplace_back(std::make_pair(str, std::move(c));)
}
