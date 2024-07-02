#pragma once

#include "SmartMovement.h"
#include "PositionMovement.h"
#include "EnemySword.h"
#include "LinkObserver.h"
#include "AttackStrategy.h"
#include "Stab.h"
#include "Standing.h"
#include "Shoot.h"

const sf::Time shootingPhaseDuration(sf::seconds(10));
const sf::Time shootInterval(sf::seconds(0.1f));

class WizardBoss : public Enemy, public LinkObserver{
public:
    WizardBoss(const sf::Texture& texture, const sf::Vector2f& position);
	~WizardBoss();

    virtual void update(const sf::Time& deltaTime) override;
	virtual sf::Vector2f getLinkPos() override;
	virtual void attack();
	virtual const sf::Vector2u& getAnimationTexturePosition(Input)override;
	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();
	void setAttackStrategy(std::unique_ptr<AttackStrategy>);
	void PerformAttack();
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	virtual std::unique_ptr<Inanimate> getAttack() override;

    bool isShootingPhase()const;
    bool m_getInvincible()const;

    //observer functions
    virtual void updateLinkPosition(const sf::Vector2f& position)override;
	virtual void removeLink() override;
	void registerAsLinkObserver(Link*);
	EnemyType getType()const;
private:
    sf::Clock m_directionChangeClock;
	Input m_currInput;

	std::unique_ptr <MovementStrategy> m_moveStrategy;
	sf::Vector2f m_linkPos;
	Link * m_link;

    sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	std::unique_ptr <AttackStrategy> m_attackStrategy;

	std::unique_ptr<Weapon> m_weapon;

    bool m_invincible;

    sf::Clock m_shootingPhaseTimer;
	sf::Clock m_shootIntervalTimer;
    bool m_shootingPhase;

    static bool m_registerit;
};