#pragma once

#include "Enemy.h"

#include "MovementStrategy.h"
#include "SmartMovement.h"
#include "PatrolMovement.h"
#include "Standing.h"
#include "EnemySword.h"
#include "LinkObserver.h"
#include "Projectile.h"/// just for test
#include "AttackStrategy.h"/// just for test
#include "Shoot.h"/// just for test
#include "Stab.h"/// just for test

#include "Link.h"

//const sf::Time invincibilityTime(sf::seconds(2));

class PigWarrior : public Enemy, public LinkObserver
{
public:
	PigWarrior(const sf::Texture& texture, const sf::Vector2f& position);
	~PigWarrior();

	virtual void update(const sf::Time& deltaTime) override;
	virtual sf::Vector2f getLinkPos() override;
	virtual void attack();
	virtual void draw(sf::RenderTarget&) override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input)override;

	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();
	void setAttackStrategy(std::unique_ptr<AttackStrategy>);
	void PerformAttack();
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	virtual std::unique_ptr<Inanimate> getAttack() override;
	

	virtual void updateLinkPosition(const sf::Vector2f& position)override;
	virtual void removeLink() override;

	void registerAsLinkObserver(Link*);

private:
	sf::Clock m_directionChangeClock;
	Input m_currInput;

	std::unique_ptr <MovementStrategy> m_moveStrategy;
	sf::Vector2f m_linkPos;
	Link * m_link;

	/// just for test
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	std::unique_ptr <AttackStrategy> m_attackStrategy;
	std::unique_ptr<Weapon> m_sword;
	///
	static bool m_registerit;
	HitBox m_lineOfSight;
};

