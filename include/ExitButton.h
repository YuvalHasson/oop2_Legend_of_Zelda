#pragma once

#include "Button.h"
#include "MainMenu.h"

class MainMenu;

class ExitButton : public Button
{
public:
	ExitButton(MainMenu* menu);

	void execute() override;
private:

};
