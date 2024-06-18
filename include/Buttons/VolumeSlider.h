#pragma once

#include <SFML/Graphics.hpp>
#include "SoundResource.h"
#include "Resources.h"

class VolumeSlider
{
public:
	VolumeSlider();
	~VolumeSlider() = default;

	void draw(sf::RenderTarget&) const;

	void update(sf::RenderWindow&);


private:
	void moveHandle(float);
	float m_volume;

	sf::RectangleShape m_slider;
	sf::RectangleShape m_sliderBar;
	sf::Text m_text;
};