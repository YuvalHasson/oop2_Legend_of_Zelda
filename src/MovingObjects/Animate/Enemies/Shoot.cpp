#include "Shoot.h"
#include <iostream>

void Shoot::attack(sf::Time& attackDuration, sf::Clock& attackTimer, std::unique_ptr<Projectile>& projectile, Enemy& enemy)
 {
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0)
    {
        if (auto p = Factory<Projectile>::instance()->create("Projectile", enemy.getPosition()))
        {
            projectile = std::move(p);
            projectile->setDirection(enemy.getDirection());
        }
        enemy.setAttacking(false);
        m_attackTimer.restart();
        std::cout << "Shoot.cpp\n";
    }
}