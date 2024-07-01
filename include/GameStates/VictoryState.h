#pragma once

#include "State.h"
#include "MainMenu.h"

class VictoryState : public State
{
public:
	VictoryState(sf::RenderWindow*);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;
};