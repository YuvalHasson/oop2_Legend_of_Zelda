#pragma once

#include "Button.h"
#include "State.h"

class BackToGameButton : public Button
{
public:
	BackToGameButton(State*);

	void execute() override;
private:

};