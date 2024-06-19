#include "Resources.h"

Resources::Resources()
{
	for (size_t i = 0; i < OBJ_AMOUNT; i++)
	{
		//will need something smarter
		sf::Image im;
		im.loadFromFile(this->m_imgName[i]);
		im.createMaskFromColor(sf::Color(0,57,115));
    	im.createMaskFromColor(sf::Color(0,128,0));
		im.createMaskFromColor(sf::Color(64, 64, 192));
		m_texture[i].loadFromImage(im);
	}
	m_icon.loadFromFile("zeldaIcon.png");
	m_font.loadFromFile("ZeldaFont.ttf");
}

Resources& Resources::getResource()
{
	static Resources resource;
	return resource;
}

sf::Font* Resources::getFont()
{
	return &m_font;
}

sf::Image* Resources::getIcon()
{
	return &m_icon;
}

sf::Texture* Resources::getTexture(int obj)
{
	return &m_texture[obj];
}
