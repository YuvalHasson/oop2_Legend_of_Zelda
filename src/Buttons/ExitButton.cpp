#include "ExitButton.h"

ExitButton::ExitButton(State* state)
{
	setText("Exit", sf::Vector2f(70, 735));
	setState(state);
}

void ExitButton::execute()
{
	getState()->exitGame();
}