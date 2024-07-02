#pragma once

#include "State.h"
#include "MainMenu.h"
#include "Board.h"
#include "PauseMenu.h"
#include "StatusBar.h"
#include "DeathState.h"
#include "SwitchLevelState.h"
#include "VictoryState.h"

class GameRunningState : public State
{
public:
	GameRunningState(sf::RenderWindow*, std::vector<Board>&&, sf::View&&, Level);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:

	void setCenterView();

	Level m_level, m_nextLevel;

	StatusBar m_statusBar;
	std::vector<Board> m_boardLevels;
	sf::View m_view;

	sf::RectangleShape m_fadingRectangle;
	bool m_won;
};