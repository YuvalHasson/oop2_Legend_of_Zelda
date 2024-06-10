#pragma once

#include "Button.h"
#include "MainMenu.h"

class MainMenu;

class LoadButton : public Button
{
public:
	LoadButton(MainMenu* menu);

	void execute() override;
private:

};
