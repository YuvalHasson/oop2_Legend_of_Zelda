#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Resources
{
private:
	std::string m_imgName[OBJ_AMOUNT] = { 
		"Zelda Menu.png", "Map.png",
		"LinkandSword.png", "Mapobject.png", "Enemies.png",
		"Zelda_status_bar.png", "Zelda_Game_Over.png", "Dungeon.png",
		"Weapons-items-hud.png", "Dungeon01.png",
		"Home.png"
	};
	sf::Texture m_texture[OBJ_AMOUNT];
	sf::Image m_icon;
	sf::Font m_font;

public:
	Resources();
	~Resources() = default;
	static Resources& getResource();

	//get
	sf::Texture* getTexture(int);
	sf::Font* getFont();
	sf::Image* getIcon();
};
