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
private:
	sf::RectangleShape m_background;
	sf::Sprite m_sprite;
	sf::Text m_text;

	sf::Time m_elapsedTime;
	sf::RectangleShape m_fadingRectangle;
	int m_direction;
};