#include "Shoot.h"

void Shoot::attack(sf::Time& attackDuration, sf::Clock& attackTimer, std::unique_ptr<Weapon>& projectile, Enemy& enemy)
 {
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0)
    {
        if (auto p = Factory<Projectile>::instance()->create("Projectile", enemy.getPosition()))
        {
            projectile = std::move(p);
			projectile->getSprite().setOrigin(enemy.getSprite().getOrigin().x / 2.f, enemy.getSprite().getOrigin().y / 2.f);
			projectile->setHitBox(sf::Vector2f(8.f, 8.f), sf::Vector2f(-3.f, -3.f));
            projectile->setDirection(enemy.getDirection());
        }
        enemy.setAttacking(false);
        m_attackTimer.restart();
    }
}