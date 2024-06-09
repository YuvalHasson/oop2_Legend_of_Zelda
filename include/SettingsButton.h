#pragma once

#include "Button.h"
#include "MainMenu.h"

class MainMenu;

class SettingsButton : public Button
{
public:
	SettingsButton(MainMenu* menu);

	void execute() override;
private:

};
