#pragma once

#include "MovingObjects.h"
#include "LinkState.h"
#include "LinkStandingState.h"


class Link : public MovingObjects
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) override;
	// virtual void attack(const sf::Time&)override;
	virtual void handleCollision() override;

private:
	std::unique_ptr<LinkState> m_state;
};