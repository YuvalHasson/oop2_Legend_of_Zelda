#include "VolumeUpButton.h"

VolumeUpButton::VolumeUpButton()
{
	setText("VolumeUp", { 70, 430 });
}

void VolumeUpButton::execute()
{
	float volumeIncreaseAmount = 10.0f;

	SoundResource::getSound().increaseBackgroundVolume(volumeIncreaseAmount);
}