#pragma once

#include "AttackStrategy.h"
#include "Utilities.h"

class Stab : public AttackStrategy
{
public:
	virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Projectile>&, Enemy& enemy) override;

private:
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	std::unique_ptr<Projectile> m_projectile;
};
