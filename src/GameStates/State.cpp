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

sf::RenderWindow* State::getWindow() const
{
	return m_window;
}

GAME_STATE State::getGameState()
{
	return m_gameState;
}
