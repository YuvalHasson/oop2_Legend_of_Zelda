#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Resources
{
private:
	std::string m_imgName[OBJ_AMOUNT] = { 
		"Zelda Menu.png", "The Legend of Zelda.png",
		"LinkandSword.png", "Mapobject.png", "Enemies.png",
		"Zelda_status_bar.png", "Zelda_Game_Over.png"
	};
	sf::Texture m_texture[OBJ_AMOUNT];
	sf::Image m_icon;
	sf::Font m_font;

public:
	Resources();
	~Resources();
	static Resources& getResource();

	//get
	sf::Texture* getTexture(int);
	sf::Font* getFont();
	sf::Image* getIcon();
};
