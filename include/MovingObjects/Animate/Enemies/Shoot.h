#pragma once

#include "Enemies/AttackStrategy.h"
#include "Projectile.h"

class Shoot : public AttackStrategy
{
public:
	virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Weapon>&, Enemy& enemy) override;

private:
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
};
