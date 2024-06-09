#pragma once

#include "InDestructible.h"

class Wall : public InDestructible
{
public:
	Wall(const sf::Texture&, const sf::Vector2f&);
	
	void handleCollision() override;
private:

};