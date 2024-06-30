#include "LoadButton.h"

LoadButton::LoadButton(State* state)
{
	setState(state);
	setText("Load", sf::Vector2f(70, 535));
}

void LoadButton::execute()
{
	getState()->loadGame();
}