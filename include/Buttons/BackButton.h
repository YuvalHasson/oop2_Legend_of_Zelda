#pragma once

#include "Button.h"
#include "State.h"

class BackButton : public Button
{
public:
	BackButton(State*);

	void execute() override;
private:

};