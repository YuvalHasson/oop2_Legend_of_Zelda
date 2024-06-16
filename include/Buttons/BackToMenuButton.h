#pragma once

#include "Button.h"
#include "State.h"

class BackToMenuButton : public Button
{
public:
	BackToMenuButton(State*);

	void execute() override;
private:

};