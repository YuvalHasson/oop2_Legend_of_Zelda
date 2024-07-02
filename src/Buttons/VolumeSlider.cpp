#include "VolumeSlider.h"

VolumeSlider::VolumeSlider()
	: m_volume(SoundResource::getSound().getVolume())
{
    m_slider.setSize(sf::Vector2f(10.f, 20.f));
    m_slider.setFillColor(sf::Color::Green);
    m_slider.setPosition(70 + (200.f * (m_volume / 100.f)), 425);

    m_sliderBar.setSize(sf::Vector2f(200.f, 10.f));
    m_sliderBar.setFillColor(sf::Color::White);
    m_sliderBar.setPosition(70, 430);

    m_text.setFont(*Resources::getResource().getFont());
    m_text.setString("Volume");
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(70, 400);
}

void VolumeSlider::draw(sf::RenderTarget& target) const
{
    target.draw(m_text);
    target.draw(m_sliderBar);
    target.draw(m_slider);
}

void VolumeSlider::update(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		m_sliderBar.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		moveHandle(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x);
	}
}

void VolumeSlider::moveHandle(float x)
{
    sf::Vector2f pos = m_sliderBar.getPosition();
    sf::Vector2f size = m_sliderBar.getSize();

    float handleX = x - m_slider.getSize().x / 2.f;

    if (handleX < pos.x)
    {
        handleX = pos.x;
    }
    else if (handleX > pos.x + size.x - m_slider.getSize().x)
    {
        handleX = pos.x + size.x - m_slider.getSize().x;
    }

    m_slider.setPosition(handleX, pos.y - (m_slider.getSize().y / 2) + (size.y / 2));

    m_volume = ((handleX - pos.x) / (size.x - m_slider.getSize().x)) * 100.f;

    SoundResource::getSound().setBackgroundVolume(m_volume);
}
