#include "ExitButton.h"

ExitButton::ExitButton(MainMenu* menu)
{
	setText("Exit", sf::Vector2f(70, 735));
	setMainMenu(menu);
}

void ExitButton::execute()
{
	getMainMenu()->exitGame();
}