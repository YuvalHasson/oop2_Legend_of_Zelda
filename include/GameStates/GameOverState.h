#pragma once

#include "State.h"
#include "MainMenu.h"
#include "LoadButton.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;

class GameOverState : public State
{
public:
	GameOverState(sf::RenderWindow*);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	void add(const std::string&, std::unique_ptr<Button>);

	sf::RectangleShape m_background;

	std::vector<Option> m_options;
};