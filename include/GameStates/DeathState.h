#pragma once

#include "State.h"
#include "Resources.h"
#include "Animation.h"
#include "GameOverState.h"

class DeathState : public State
{
public:
	DeathState(sf::RenderWindow*, sf::Vector2f);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	sf::RectangleShape m_whiteBackground;
	sf::Sprite m_linkDeathSprite;

	int m_amountOfSpins;

	Animation m_animation;
};