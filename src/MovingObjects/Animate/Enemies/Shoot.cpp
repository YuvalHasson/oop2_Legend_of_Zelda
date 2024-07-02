#include "Shoot.h"

void Shoot::attack(sf::Time&, sf::Clock&, std::unique_ptr<Weapon>& projectile, Enemy& enemy)
 {
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0)
    {
        if (auto p = Factory<Projectile>::instance()->create("Projectile", { enemy.getPosition().x + 5, enemy.getPosition().y + 5 }))
        {
            projectile = std::move(p);
            projectile->setDirection(enemy.getDirection());
        }
        enemy.setAttacking(false);
        m_attackTimer.restart();
    }
}