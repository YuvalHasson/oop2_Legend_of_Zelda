#include "State.h"

GAME_STATE State::m_gameState = GAME_STATE::MAIN_MENU;

State::State(sf::RenderWindow* window)
	: m_window(window)
{
}

void State::updateState(GAME_STATE gameState)
{
	m_gameState = gameState;
}

void State::startGame()
{
	updateState(GAME_STATE::NEW_GAME);
}

void State::exitGame()
{
	updateState(GAME_STATE::EXIT);
}

void State::openSettings()
{
	updateState(GAME_STATE::SETTINGS);
}

void State::backToMenu()
{
	updateState(GAME_STATE::MAIN_MENU);
}

sf::RenderWindow* State::getWindow() const
{
	return m_window;
}

GAME_STATE State::getGameState()
{
	return m_gameState;
}
