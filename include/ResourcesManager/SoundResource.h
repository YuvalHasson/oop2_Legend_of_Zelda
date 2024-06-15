#pragma once

#include "Utilities.h"
#include <SFML/Audio.hpp>

class SoundResource
{
private:
	std::string m_soundNames[SOUND_AMOUNT] = {
		""
	};

	std::string m_backgroundNames[BACK_SOUND_AMNT] = {
		"MainTheme.ogg", "LinkAwakens.ogg"
	};

	sf::Music m_backgroundMusic[BACK_SOUND_AMNT];
	sf::SoundBuffer m_buffers[SOUND_AMOUNT];;
	sf::Sound m_sounds[SOUND_AMOUNT];

	float m_backgroundVolume;

public:
	SoundResource();
	~SoundResource() = default;

	static SoundResource& getSound();

	void playSound(int);
	void playBackground(int);
	void stopBackground(int);

	void setBackgroundVolume(float);
	
	float getVolume() const;
};