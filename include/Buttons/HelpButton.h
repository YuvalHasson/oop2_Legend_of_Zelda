#pragma once

#include "Button.h"
#include "State.h"

class HelpButton : public Button
{
public:
	HelpButton(State*);

	void execute() override;
private:

};
