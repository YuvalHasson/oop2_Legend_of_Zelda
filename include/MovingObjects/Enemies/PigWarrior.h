#pragma once

#include "Enemy.h"

#include "MovementStrategy.h"
#include "StandingState.h"
#include "SmartMovement.h"
#include "PatrolMovement.h"
#include "AttackingState.h"
#include "Sword.h"

#include "Link.h"

//const sf::Time invincibilityTime(sf::seconds(2));

class PigWarrior : public Enemy
{
public:
	PigWarrior(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(const sf::Time& deltaTime) override;
	//virtual void attack(const sf::Time& deltaTime) override;
	virtual void handleCollision() override;
	virtual void attack();
	const sf::Vector2u& getAnimationTexturePosition(Input);
	void setMoveStrategy(std::unique_ptr<MovementStrategy>&);
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	virtual std::unique_ptr<MovingObjects> getAttack() override;

	void UpdateLinkPos(const sf::Vector2f& position);

	void insertSword(Sword*);

	void swipeSword();
	void stopSwordSwipe();

	bool getInvincible()const;
	void initializeInvincible();

private:
	sf::Clock m_directionChangeClock;
	Input m_currInput;

	std::unique_ptr <MovementStrategy> m_moveStrategy;
	sf::Vector2f m_linkPos;

	static bool m_registerit;
	Sword* m_sword;

	sf::Clock m_invincibleTimer;
};

