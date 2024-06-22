#pragma once

#include "MovingObjects.h"
#include "LinkState.h"
#include "LinkStandingState.h"
#include "LinkShieldStandingState.h"
#include "Sword.h"
#include "LinkArrow.h"
#include "LinkSubject.h"
#include "Shield.h"

const sf::Time invincibilityTime(sf::seconds(2));

class Link : public MovingObjects, public LinkSubject
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) override;
	virtual void draw(sf::RenderTarget& ) override;
	virtual void handleCollision() override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };
	virtual void move()override;

	//observer list functions
	virtual void RegisterObserver(LinkObserver* observer)override;
	virtual void RemoveObserver(LinkObserver* observer)override;
	virtual void NotifyObservers()override;


	void swipeSword();
	void stopSwordSwipe();
	void shoot();
	void stopShooting();

	bool getInvincible() const;
	void initializeInvincible();

	Sword* getSword();
	virtual std::unique_ptr<MovingObjects> getAttack() override;
	Shield* getShield();

	void setPush(bool);
	bool isPush() const;
	bool getShooting() const;
	bool getShielding()const;
private:
	std::unique_ptr<LinkState> m_state;
	std::unique_ptr<Sword> m_sword;
	std::unique_ptr<LinkArrow> m_arrow;
	std::unique_ptr<Shield> m_shield;
	sf::Clock m_invincibleTimer;
	bool m_isPushing;
	bool m_isShooting;
	bool m_wasTabPressed;
	bool m_isShielding;
  	static bool m_registerit;
	std::vector<LinkObserver*> m_observers;

};