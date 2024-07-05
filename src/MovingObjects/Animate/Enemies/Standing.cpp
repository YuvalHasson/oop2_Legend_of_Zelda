#include "Standing.h"

void Standing::move(Input& direction, Enemy&, sf::Clock* directionChangeClock)
{
	if (directionChangeClock->getElapsedTime().asSeconds() >= 1.0f)
	{
		direction = STANDING;
		directionChangeClock->restart();
	}
}
