#include "SettingsButton.h"

SettingsButton::SettingsButton(State* state)
{
	setText("Settings", sf::Vector2f(70, 635));
	setState(state);
}

void SettingsButton::execute()
{
	getState()->openSettings();
}