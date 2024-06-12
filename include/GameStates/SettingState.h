#pragma once

#include "State.h"
#include "SoundResource.h"
#include "MainMenu.h"
#include "BackButton.h"
#include "VolumeDownButton.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;

class SettingState : public State
{
public:
	SettingState(sf::RenderWindow* window);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

private:
	void add(const std::string&, std::unique_ptr<Button>);

	sf::RectangleShape m_menuBackground;
	std::vector<Option> m_options;
};