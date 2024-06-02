#pragma once

#include <SFML/GRAPHICS.hpp>
#include "Utilities.h"
#include "Resources.h"

class Controller
{
public:
	Controller();
	~Controller();

	void run();
private:
	sf::RenderWindow m_window;
};