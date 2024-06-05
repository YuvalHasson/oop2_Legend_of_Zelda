#pragma once

#include <SFML/GRAPHICS.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "MainMenu.h"
#include "Board.h"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

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