#include "SaveButton.h"

SaveButton::SaveButton(State* state)
{
	setText("Save", sf::Vector2f(70, 650));
	setState(state);
}

void SaveButton::execute()
{
	getState()->saveGame();
}
