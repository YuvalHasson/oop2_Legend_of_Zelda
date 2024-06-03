#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Resources
{
private:
	std::string m_imgName[OBJ_AMOUNT] = { 
		"Stick.png", "Zelda Menu.png", "Button.png",
		"Scoreboard.png", "Clock.png", "EndGameScreen.png", "HelpButton.png", "SaveButton.png",
		"The Legend of Zelda.png"
	};
	sf::Texture m_texture[OBJ_AMOUNT];
	sf::Font m_font;

public:
	Resources();
	~Resources();
	static Resources& getResource();

	//get
	sf::Texture* getTexture(int);
	sf::Font* getFont();
};
