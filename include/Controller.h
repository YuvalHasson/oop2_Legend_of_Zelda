#pragma once

#include <SFML/GRAPHICS.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "MainMenu.h"
#include "Board.h"

//#include "MyContactListener.h"

class Controller
{
public:
	Controller();
	~Controller();

	void run();
private:
	sf::RenderWindow m_window;

	Board m_board;
	MainMenu m_mainMenu;


	int m_gameState;
};