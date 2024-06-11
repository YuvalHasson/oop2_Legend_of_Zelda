#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"

class State;

class Button
{
public:
	Button();
	virtual ~Button() = default;

	virtual void execute() = 0;
	void draw(sf::RenderWindow&) const;
	void setState(State*);

	void setText(std::string, sf::Vector2f);
	void overButton(sf::RenderWindow&);

	bool isButtonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);

	State* getState() const;

private:
	State* m_state;

	sf::Text m_text;
};