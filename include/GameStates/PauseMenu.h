#pragma once

#include "State.h"
#include "Board.h"
#include "MainMenu.h"
#include "SaveState.h"

#include "ExitButton.h"
#include "SaveButton.h"
#include "BackToGameButton.h"
#include "VolumeSlider.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;


class PauseMenu : public State
{
public:
	PauseMenu(sf::RenderWindow*, std::vector<Board>&&, sf::View&&, Level);
	
	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	void setCenterView();

	void add(const std::string&, std::unique_ptr<Button>);

	VolumeSlider m_volumeSlider;
	Level m_level;
	std::vector<Board> m_boardLevels;

	sf::View m_view;

	sf::RectangleShape m_pauseBackground;

	sf::RectangleShape m_controls;

	std::vector<Option> m_options;
};