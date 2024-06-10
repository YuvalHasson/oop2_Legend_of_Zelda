#pragma once

#include "Enemy.h"
#include "OctorokState.h"
#include "OctorokStandingState.h"

class Octorok : public Enemy
{
public:
	Octorok(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(const sf::Time& deltaTime) override;
	//virtual void attack(const sf::Time& deltaTime) override;
	virtual void handleCollision() override;

	virtual void move() override;

private:
	sf::Clock m_directionChangeClock;
	std::unique_ptr<OctorokState> m_state;
};