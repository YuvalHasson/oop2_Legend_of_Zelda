#pragma once

#include <SFML/GRAPHICS.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "SoundResource.h"
#include "MainMenu.h"

#include "State.h"

class Controller
{
public:
	Controller();
	~Controller() = default;

	void run();
private:
	sf::RenderWindow m_window;

	std::unique_ptr<State> m_state;
};