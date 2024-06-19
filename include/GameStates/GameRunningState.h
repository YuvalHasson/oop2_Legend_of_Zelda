#pragma once

#include "State.h"
#include "MainMenu.h"
#include "Board.h"
#include "PauseMenu.h"
#include "StatusBar.h"
#include "DeathState.h"

class GameRunningState : public State
{
public:
	GameRunningState(sf::RenderWindow*, Board&&, sf::View&&, sf::Sprite);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:

	void setCenterView();

	StatusBar m_statusBar;
	Board m_board;
	sf::View m_view;
	sf::Sprite m_background;
};