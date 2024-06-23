#include "SwitchLevelState.h"

SwitchLevelState::SwitchLevelState(sf::RenderWindow* window, std::vector<Board>&& baord, sf::View&& view, Level level)
	:State(window), m_boardLevels(std::move(baord)), m_view(std::move(view)), m_level(level)
{
}

void SwitchLevelState::update(const sf::Time& deltaTime)
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
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view));
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void SwitchLevelState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}
