#pragma once

#include "Button.h"
#include "State.h"

class ExitButton : public Button
{
public:
	ExitButton(State*);

	void execute() override;
private:

};
