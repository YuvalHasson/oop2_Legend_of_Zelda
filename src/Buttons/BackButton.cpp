#include "BackButton.h"

BackButton::BackButton(State* state)
{
	setText("Back", sf::Vector2f(70, 735));
	setState(state);
}

void BackButton::execute()
{
	getState()->backToMenu();
}