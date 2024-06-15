#include "ExitButton.h"

ExitButton::ExitButton(State* state)
{
	setText("Exit", sf::Vector2f(900, 750));
	setState(state);
}

void ExitButton::execute()
{
	getState()->exitGame();
}