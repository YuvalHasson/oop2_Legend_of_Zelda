#pragma once

#include "Enemies/AttackStrategy.h"
//#include "Projectile.h"
#include "Utilities.h"
//#include "Enemy.h"

class Shoot : public AttackStrategy
{
public:
	virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Projectile>&, Enemy& enemy) override;

private:
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	std::unique_ptr<Projectile> m_projectile;
	bool m_isAnimationSet;
};
