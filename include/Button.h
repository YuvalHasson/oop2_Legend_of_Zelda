#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class Button
{
public:
	Button();
	virtual ~Button() = default;

	void draw(sf::RenderWindow&) const;
	//void createButton(sf::Vector2f, sf::Vector2f);
	void setText(std::string, sf::Vector2f);

	bool isButtonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);

private:
	sf::RectangleShape m_button;
	sf::Text m_text;
};