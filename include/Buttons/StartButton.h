#pragma once

#include "Button.h"
#include "State.h"

class StartButton : public Button
{
public:
	StartButton(State*);

	virtual void execute() override;
private:

};