#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "StartButton.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu() = default;

	void drawMainMenu(sf::RenderWindow&);

	int buttonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);
	
private:
	sf::RectangleShape m_menuBackground;
	std::unique_ptr<Button> m_button;
};