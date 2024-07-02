#include "Standing.h"

void Standing::move(Input& direction, Enemy&, sf::Clock* directionChangeClock)
{
	if (directionChangeClock->getElapsedTime().asSeconds() >= 1.0f) // Change direction every 1 seconds
	{
		direction = STANDING;
		directionChangeClock->restart();
	}
}
