#include "Weapon.h"

Weapon::Weapon(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: Inanimate(texture, position, size, originOffset) {}