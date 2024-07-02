#pragma once

#include "Utilities.h"
#include "Weapon.h"
#include "Enemy.h"

class AttackStrategy
{
public:
    virtual ~AttackStrategy() = default;
    virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Weapon>&, Enemy& enemy) = 0;
};