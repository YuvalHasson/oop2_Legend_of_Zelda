#pragma once

#include "Animate.h"
#include "LinkState.h"
#include "LinkStandingState.h"
#include "LinkShieldStandingState.h"
#include "Sword.h"
#include "LinkArrow.h"
#include "LinkSubject.h"
#include "Shield.h"
#include "ColorAnimation.h"

const sf::Time invincibilityTime(sf::seconds(2));


class Link : public Animate, public LinkSubject
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);
	~Link();

	virtual void update(const sf::Time&) override;
	virtual void draw(sf::RenderTarget& ) override;

	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };
	virtual void move() override;

	//observer list functions
	virtual void RegisterObserver(LinkObserver*) override;
	virtual void RemoveObserver(LinkObserver*) override;
	virtual void NotifyObservers() override;
	virtual void NotifyObserversLinkOut() const override;


	void swipeSword();
	void stopSwordSwipe();
	void shoot();
	void stopShooting();

	bool getInvincible();
	void initializeInvincible();

	Sword* getSword();
	Shield* getShield();
	virtual std::unique_ptr<Inanimate> getAttack() override;

	void takeSword();
	void takeBow();
	Weapons getCurrentWeapon() const;

	void setPush(bool);
	bool isPush() const;
	bool getShooting() const;

	void resetTimeSinceLastPushed();
private:
	//current link state
	std::unique_ptr<LinkState> m_state;
	
	//activity members
	std::unique_ptr<Sword> m_sword;
	std::unique_ptr<LinkArrow> m_arrow;
	std::unique_ptr<Shield> m_shield;
	
	//invincibility
	sf::Clock m_invincibleTimer;
	
	//acticity variables
	bool m_isPushing;
	bool m_isShooting;
	bool m_wasTabPressed;
	bool m_isShielding;
	bool m_invincible;

	sf::Clock m_timeSinceLastPush;

	//weapons currently held
	std::vector<Weapons> m_weapons;
	size_t m_currentWeapon;

	//factory registration variable
  	static bool m_registerit;
	
	//observers vector
	std::vector<LinkObserver*> m_observers;
};