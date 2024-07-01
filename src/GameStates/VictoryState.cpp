#include "VictoryState.h"

VictoryState::VictoryState(sf::RenderWindow* window)
	: State(window) {}

void VictoryState::update(const sf::Time&)
{
	updateState(GAME_STATE::MAIN_MENU);
}

void VictoryState::render(sf::RenderTarget* target)
{
	if (target == nullptr)
	{
		target = getWindow();
	}
}

std::unique_ptr<State> VictoryState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void VictoryState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}