#pragma once

#include "Button.h"
#include "State.h"

class SaveButton : public Button
{
public:
	SaveButton(State*);

	void execute() override;
private:

};
