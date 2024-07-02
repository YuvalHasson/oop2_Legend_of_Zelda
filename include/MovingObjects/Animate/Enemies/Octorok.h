#pragma once

#include "Enemy.h"
#include "Link.h"

#include "Projectile.h"

#include "MovementStrategy.h"
#include "AttackStrategy.h"
#include "PatrolMovement.h"
#include "Shoot.h"
#include "Standing.h"

class Octorok : public Enemy
{
public:
	Octorok(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(const sf::Time& deltaTime) override;
	virtual void attack();
	virtual sf::Vector2f getLinkPos() override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override;
	virtual EnemyType getType() const override;

	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();
	void setAttackStrategy(std::unique_ptr<AttackStrategy>);
	void PerformAttack();

	virtual std::unique_ptr<Inanimate> getAttack() override;

private:
	sf::Clock m_directionChangeClock;
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	Input m_currInput;
	std::unique_ptr <MovementStrategy> m_moveStrategy;
	std::unique_ptr <AttackStrategy> m_attackStrategy;

	std::unique_ptr<Weapon> m_projectile;

	static bool m_registerit;
};