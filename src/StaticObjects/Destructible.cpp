#include "Destructible.h"


Destructible::Destructible(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: StaticObjects(texture, position, size, originOffset) {}