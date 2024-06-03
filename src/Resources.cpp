#include "Resources.h"

Resources::Resources()
{
	for (size_t i = 0; i < OBJ_AMOUNT; i++)
	{
		this->m_texture[i].loadFromFile(this->m_imgName[i]);
	}
	this->m_font.loadFromFile("ZeldaFont.ttf");
}

Resources::~Resources()
{
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

sf::Texture* Resources::getTexture(int obj)
{
	return &m_texture[obj];
}
