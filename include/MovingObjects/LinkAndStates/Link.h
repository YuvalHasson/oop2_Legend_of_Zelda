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
	virtual void handleCollision() override;
	void insertSword(Sword*);


	void swipeSword();
	void stopSwordSwipe();
	bool getInvincible()const;
	void initializeInvincible();

	void setPush(bool);
	bool isPush() const;
private:
	bool m_isPushing;
	std::unique_ptr<LinkState> m_state;
	Sword* m_sword;
	sf::Clock m_invincibleTimer;
  	static bool m_registerit;

};