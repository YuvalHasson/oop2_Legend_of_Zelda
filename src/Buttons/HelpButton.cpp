#include "HelpButton.h"

HelpButton::HelpButton(State* state)
{
	setText("Help", sf::Vector2f(70, 585));
	setState(state);
}

void HelpButton::execute()
{
	getState()->openHelp();
}