#pragma once

#include "State.h"
#include "Board.h"
#include "MainMenu.h"

#include "ExitButton.h"
#include "BackToGameButton.h"
#include "VolumeSlider.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;


class PauseMenu : public State
{
public:
	PauseMenu(sf::RenderWindow*, Board&&, sf::View&&, sf::Sprite);
	
	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	void setCenterView();

	void add(const std::string&, std::unique_ptr<Button>);

	VolumeSlider m_volumeSlider;

	Board m_board;
	sf::View m_view;
	sf::Sprite m_background;

	std::vector<Option> m_options;
};