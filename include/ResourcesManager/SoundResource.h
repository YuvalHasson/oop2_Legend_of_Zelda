#pragma once

#include "Utilities.h"
#include <SFML/Audio.hpp>

class SoundResource
{
private:
	std::string m_soundNames[SOUND_AMOUNT] = {
		"DeathSound.ogg", "LinkGetSword.ogg", "LinkBowArrow.ogg", "LinkDamage.ogg",
		"LinkSwordSlash01.ogg", "LinkSwordSlash02.ogg", "LinkSwordSlash03.ogg", "LinkSwordSlash04.ogg",
		"LinkGetItem.ogg", "EnemyHit.ogg", "EnemyDie.ogg",
		"SeaUrchinPush1.ogg", "SeaUrchinPush2.ogg",
		"PauseMenuOpen.ogg", "PauseMenuClose.ogg",
		"BushCut.ogg", "ShieldDeflect.ogg"
	};

	std::string m_backgroundNames[BACK_SOUND_AMNT] = {
		"MainTheme.ogg", "House.ogg", "Overworld.ogg", "GameOver.ogg", "Dungeon01.ogg",
		"KeyDungeon.ogg", "DontGoDungeon.ogg", "BossDungeon.ogg", "Ending.ogg"
	};

	sf::Music m_backgroundMusic[BACK_SOUND_AMNT];
	sf::SoundBuffer m_buffers[SOUND_AMOUNT];
	sf::Sound m_sounds[SOUND_AMOUNT];

	float m_backgroundVolume;

public:
	SoundResource();
	~SoundResource() = default;

	static SoundResource& getSound();

	void playSound(int);
	void playBackground(int);
	void StopBackground();

	void setBackgroundVolume(float);
	
	const float getVolume() const;
};