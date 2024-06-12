#pragma once

#include "Button.h"
#include "SoundResource.h"

class VolumeDownButton : public Button
{
public:
	VolumeDownButton();

	void execute() override;
};