#pragma once

//pushable object

#include "Inanimate/Inanimate.h"

class Boulder : public Inanimate
{
public:
	Boulder(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;

private:
	static bool m_registerit;
};