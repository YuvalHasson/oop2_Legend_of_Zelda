#pragma once

#include "Enemy.h"
#include "OctorokState.h"
#include "OctorokStandingState.h"

#include "OctorokProjectile.h"

class Octorok : public Enemy
{
public:
	Octorok(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(const sf::Time& deltaTime) override;
	virtual void attack();
	virtual void handleCollision() override;

	// virtual void move() override;
	virtual std::unique_ptr<MovingObjects> getAttack() override;

private:
	sf::Clock m_directionChangeClock;
	std::unique_ptr<OctorokState> m_state;

	std::unique_ptr<OctorokProjectile> m_projectile;

	static bool m_registerit;
};