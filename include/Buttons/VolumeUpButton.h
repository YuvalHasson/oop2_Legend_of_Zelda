#pragma once

#include "Button.h"
#include "SoundResource.h"

class VolumeUpButton : public Button
{
public:
	VolumeUpButton();

	void execute() override;
};