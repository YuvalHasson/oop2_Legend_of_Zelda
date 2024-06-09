#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class MainMenu;

class Button
{
public:
	Button();
	virtual ~Button() = default;

	virtual void execute() = 0;
	void draw(sf::RenderWindow&) const;
	void setMainMenu(MainMenu*);
	
	void setText(std::string, sf::Vector2f);

	bool isButtonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);
	MainMenu* getMainMenu() const;

private:
	MainMenu* m_mainMenu;

	sf::Text m_text;
};