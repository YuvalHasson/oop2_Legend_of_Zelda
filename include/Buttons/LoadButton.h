#pragma once

#include "Button.h"
#include "State.h"

class LoadButton : public Button
{
public:
	LoadButton(State*);

	void execute() override;
private:

};
