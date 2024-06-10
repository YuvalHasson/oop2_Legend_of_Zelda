#pragma once

#include "Enemy.h"

class Octorok : public Enemy
{
public:
	Octorok(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(const sf::Time& deltaTime);
	virtual void attack(const sf::Time& deltaTime);
	virtual void handleCollision();

private:

};