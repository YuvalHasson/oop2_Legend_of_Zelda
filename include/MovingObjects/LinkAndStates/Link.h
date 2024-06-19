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
	virtual void draw(sf::RenderTarget& ) override;
	virtual void handleCollision() override;
	void insertSword(Sword*);
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };



	void swipeSword();
	void stopSwordSwipe();
	bool getInvincible()const;
	void initializeInvincible();

	Sword* getSword();


	void setPush(bool);
	bool isPush() const;
private:
	std::unique_ptr<LinkState> m_state;
	std::unique_ptr<Sword> m_sword;
	sf::Clock m_invincibleTimer;
	bool m_isPushing;
  	static bool m_registerit;

};