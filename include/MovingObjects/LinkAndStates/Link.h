#pragma once

#include "MovingObjects.h"
#include "LinkState.h"
#include "LinkStandingState.h"
#include "Sword.h"
#include "LinkArrow.h"

const sf::Time invincibilityTime(sf::seconds(2));

class Link : public MovingObjects
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) override;
	virtual void draw(sf::RenderTarget& ) override;
	virtual void handleCollision() override;
	void insertSword(Sword*);
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };



	void swipeSword();
	void stopSwordSwipe();
	void shoot();
	void stopShooting();

	bool getInvincible()const;
	void initializeInvincible();

	Sword* getSword();
	virtual std::unique_ptr<MovingObjects> getAttack()override;

	void setPush(bool);
	bool isPush() const;
	bool getShooting()const;
private:
	std::unique_ptr<LinkState> m_state;
	std::unique_ptr<Sword> m_sword;
	std::unique_ptr<LinkArrow> m_arrow;
	sf::Clock m_invincibleTimer;
	bool m_isPushing;
	bool m_isShooting;
  	static bool m_registerit;

};