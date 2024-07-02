#pragma once

#include "AttackStrategy.h"
#include "EnemySword.h"
#include "Utilities.h"

class Stab : public AttackStrategy
{
public:
	virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Weapon>&, Enemy&) override;

private:
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
};
