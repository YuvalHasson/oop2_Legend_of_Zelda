#pragma once

#include "Enemy.h"

#include "MovementStrategy.h"
#include "SmartMovement.h"
#include "PatrolMovement.h"
#include "Standing.h"
#include "EnemySword.h"
#include "LinkObserver.h"
#include "AttackStrategy.h"
#include "Stab.h"

#include "Link.h"

class PigWarrior : public Enemy, public LinkObserver
{
public:
	PigWarrior(const sf::Texture&, const sf::Vector2f&);
	~PigWarrior();

	virtual void update(const sf::Time&) override;
	virtual sf::Vector2f getLinkPos() override;
	virtual void attack();
	virtual const sf::Vector2u getAnimationTexturePosition(Input) override;
	virtual EnemyType getType() const override;

	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();
	void setAttackStrategy(std::unique_ptr<AttackStrategy>);
	void PerformAttack();
	float distance(const sf::Vector2f&, const sf::Vector2f&);

	virtual std::unique_ptr<Inanimate> getAttack() override;
	
	virtual void updateLinkPosition(const sf::Vector2f&) override;
	virtual void removeLink() override;
	void registerAsLinkObserver(Link*);
	
private:
	sf::Clock m_directionChangeClock;
	Input m_currInput;

	std::unique_ptr <MovementStrategy> m_moveStrategy;
	sf::Vector2f m_linkPos;
	Link* m_link;

	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	std::unique_ptr <AttackStrategy> m_attackStrategy;
	std::unique_ptr<Weapon> m_sword;
	static bool m_registerit;
};

