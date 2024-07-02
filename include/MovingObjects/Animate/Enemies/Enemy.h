#pragma once

#include "Animate.h"

const sf::Time EnemyHitAnimationTime(sf::seconds(1.f));

class Enemy : public Animate
{
public:
	Enemy(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
	virtual sf::Vector2f getLinkPos() = 0;
	virtual std::unique_ptr<Inanimate> getAttack() override = 0;
	virtual void update(const sf::Time& )override;
	virtual void updateHitAnimation(const sf::Time& )override;
	bool isHittingObjects(const sf::Vector2f&)const;
	bool castRay(const sf::Vector2f& ,const sf::Vector2f&)const;
	void hit();

	virtual EnemyType getType() const = 0;

private:
	sf::Clock m_hitTimer;
	bool m_isHit;
};