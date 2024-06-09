#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "StartButton.h"

using Option = std::pair<std::string, std::unique_ptr<Button>>;

class MainMenu
{
public:
	MainMenu();
	~MainMenu() = default;

	void drawMainMenu(sf::RenderWindow&);
	void buttonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);
	void startGame();
	void setGameState(int);

	int getGameState() const;

private:
	void add(const std::string&, std::unique_ptr<Button>);

	sf::RectangleShape m_menuBackground;
	std::vector<Option> m_options;

	int m_gameState;
};