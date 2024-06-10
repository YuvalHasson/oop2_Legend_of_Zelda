#include "StartButton.h"

StartButton::StartButton(MainMenu* menu)
{
	setText("Start", sf::Vector2f(70, 485));
	setMainMenu(menu);
}

void StartButton::execute()
{
	getMainMenu()->startGame();
}
