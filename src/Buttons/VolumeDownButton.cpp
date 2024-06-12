#include "VolumeDownButton.h"	

VolumeDownButton::VolumeDownButton()
{
	setText("Volume-", { 70, 400 });
}

void VolumeDownButton::execute()
{
	float volumeIncreaseAmount = 10.0f;

	SoundResource::getSound().decreaseBackgroundVolume(volumeIncreaseAmount);
}