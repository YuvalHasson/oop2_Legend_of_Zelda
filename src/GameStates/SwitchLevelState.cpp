#include "SwitchLevelState.h"

SwitchLevelState::SwitchLevelState(sf::RenderWindow* window, std::vector<Board>&& baord, sf::View&& view, Level level, Level nextLevel)
	:State(window), m_boardLevels(std::move(baord)), m_view(std::move(view)), m_level(nextLevel)
{
	m_link = std::move(m_boardLevels[level].extractLink());
	m_boardLevels[m_level].setLink(std::move(m_link));
	m_boardLevels[m_level].initializeLevel(m_level);
	m_boardLevels[m_level].resetEnemiesAndInanimated();
}

void SwitchLevelState::update(const sf::Time&)
{
	updateState(GAME_STATE::GAME_RUNNING);
}

void SwitchLevelState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);
}

std::unique_ptr<State> SwitchLevelState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::GAME_RUNNING)
	{
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level);
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void SwitchLevelState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}
