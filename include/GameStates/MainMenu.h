#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "SettingsButton.h"
#include "HelpButton.h"
#include "LoadButton.h"

#include "State.h"
#include "SettingState.h"
#include "NewGameState.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;

class MainMenu : public State
{
public:
	MainMenu(sf::RenderWindow*);


	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	void overButton(sf::RenderWindow&);
	void add(const std::string&, std::unique_ptr<Button>);

	sf::RectangleShape m_menuBackground;
	std::vector<Option> m_options;
};