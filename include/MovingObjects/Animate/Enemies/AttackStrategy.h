#pragma once

#include "Utilities.h"
#include "Projectile.h"
#include "Enemy.h"
//#include "MovementStrategy.h"


class AttackStrategy
{
public:
    virtual ~AttackStrategy() = default;
    virtual void attack(sf::Time&, sf::Clock&, std::unique_ptr<Projectile>&, Enemy& enemy) = 0;
};