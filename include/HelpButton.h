#pragma once

#include "Button.h"
#include "MainMenu.h"

class MainMenu;

class HelpButton : public Button
{
public:
	HelpButton(MainMenu* menu);

	void execute() override;
private:

};
