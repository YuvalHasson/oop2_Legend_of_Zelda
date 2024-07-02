#include "Stab.h"

void Stab::attack(sf::Time&, sf::Clock&, std::unique_ptr<Weapon>& sword, Enemy& enemy)
{
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0)
    {
        if (auto p = Factory<EnemySword>::instance()->create("EnemySword", enemy.getPosition()))
        {
            sword = std::move(p);
            sword->setDirection(enemy.getDirection());
            sf::Vector2f position = enemy.getPosition();
            sf::Vector2f attackPos;
            if (enemy.getDirection().x == 1) {
                sword.get()->setGraphics(ANIMATIONS_POSITIONS::EnemySwordRight, 2, true, 0.10f);//true for singleTime
                attackPos.x = position.x + tileSize * 0.71f;
                attackPos.y = position.y;
            }
            else if (enemy.getDirection().x == -1) {
                sword.get()->setGraphics(ANIMATIONS_POSITIONS::EnemySwordLeft, 1);//true for singleTime
                attackPos.x = position.x - tileSize * 0.71f;
                attackPos.y = position.y;
            }
            else if (enemy.getDirection() == DIRECTIONS::Up) {
                sword.get()->setGraphics(ANIMATIONS_POSITIONS::EnemySwordUp, 1);//true for singleTime
                attackPos.x = position.x;
                attackPos.y = position.y - tileSize * 0.71f;
            }
            else if (enemy.getDirection() == DIRECTIONS::Down) {
                sword->setGraphics(ANIMATIONS_POSITIONS::EnemySwordDown, 1);//true for singleTime
                attackPos.x = position.x - 0.1f;
                attackPos.y = position.y + tileSize * 0.65f;
            }
            sword->setPosition(attackPos);
            sword->updateSprite();
        
            enemy.setAttacking(false);
            m_attackTimer.restart();
        }       
    }
}
