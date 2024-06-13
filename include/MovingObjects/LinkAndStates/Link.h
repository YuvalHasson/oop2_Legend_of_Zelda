#pragma once

#include "MovingObjects.h"
#include "LinkState.h"
#include "LinkStandingState.h"
#include "Sword.h"


class Link : public MovingObjects
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) override;
	// virtual void attack(const sf::Time&)override;
	virtual void handleCollision() override;
	//void createSword();
	//void killSword();
	void insertSword(Sword*);

	void undoMove();
	bool isAttacking() const;
	void swipeSword();
	void stopSwordSwipe();

private:
	std::unique_ptr<LinkState> m_state;
	Sword* m_sword;
};