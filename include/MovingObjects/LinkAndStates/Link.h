#pragma once

#include "MovingObjects.h"
#include "LinkState.h"
#include "LinkStandingState.h"
#include "Sword.h"

const sf::Time invincibilityTime(sf::seconds(2));

class Link : public MovingObjects
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) override;
	// virtual void attack(const sf::Time&) override;
	virtual void handleCollision() override;
	//void createSword();
	//void killSword();
	void insertSword(Sword*);
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };



	// bool isAttacking() const;
	void swipeSword();
	void stopSwordSwipe();

	bool getInvincible()const;
	void initializeInvincible();

private:
	std::unique_ptr<LinkState> m_state;
	Sword* m_sword;
	sf::Clock m_invincibleTimer;
  	static bool m_registerit;

};