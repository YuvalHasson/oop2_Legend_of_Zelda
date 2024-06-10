#include "SettingsButton.h"

SettingsButton::SettingsButton(MainMenu* menu)
{
	setText("Settings", sf::Vector2f(70, 635));
	setMainMenu(menu);
}

void SettingsButton::execute()
{
	//getMainMenu()->openSettings();
}