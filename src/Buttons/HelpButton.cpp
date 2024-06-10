#include "HelpButton.h"

HelpButton::HelpButton(MainMenu* menu)
{
	setText("Help", sf::Vector2f(70, 585));
	setMainMenu(menu);
}

void HelpButton::execute()
{
	//getMainMenu()->setHelpMenu();
}