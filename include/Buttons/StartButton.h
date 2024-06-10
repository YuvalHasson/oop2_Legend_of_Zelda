#pragma once

#include "Button.h"
#include "MainMenu.h"

class StartButton : public Button
{
public:
	StartButton(MainMenu*);

	virtual void execute() override;
private:

};