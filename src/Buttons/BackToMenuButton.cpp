#include "BackToMenuButton.h"

BackToMenuButton::BackToMenuButton(State* state)
{
	setText("Menu", sf::Vector2f(70, 700));
	setState(state);
}

void BackToMenuButton::execute()
{
	getState()->backToMenu();
}