#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "Button.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu() = default;

	void drawMainMenu(sf::RenderWindow&);

	int buttonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);
	
private:
	sf::RectangleShape m_menuBackground;
	Button m_Button;
};