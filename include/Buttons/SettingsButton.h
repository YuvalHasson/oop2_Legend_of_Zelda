#pragma once

#include "Button.h"
#include "State.h"

class SettingsButton : public Button
{
public:
	SettingsButton(State*);

	void execute() override;
private:

};
