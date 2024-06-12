#pragma once

#include "State.h"
#include "MainMenu.h"
#include "GameRunningState.h"
#include "Board.h"

class NewGameState : public State
{
public:
	NewGameState(sf::RenderWindow*);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	sf::Sprite m_background;

	Board m_board;
	sf::View m_view;
};
