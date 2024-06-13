#include "StartButton.h"

StartButton::StartButton(State* menu)
{
	setText("Start", sf::Vector2f(70, 485));
	setState(menu);
}

void StartButton::execute()
{
	getState()->startGame();
}
