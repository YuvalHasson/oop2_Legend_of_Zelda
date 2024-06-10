#include "LoadButton.h"

LoadButton::LoadButton(MainMenu* menu)
{
	setMainMenu(menu);
	setText("Load", sf::Vector2f(70, 535));
}

void LoadButton::execute()
{
	//getMainMenu()->setLoadMenu();
}