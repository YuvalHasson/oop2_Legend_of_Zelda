#pragma once

#include "MovingObjects.h"

#include "Inanimate/Inanimate.h"
#include "ColorAnimation.h"

const sf::Time pushbackDuration(sf::seconds(0.3f));

class Animate : public MovingObjects
{
public:
	Animate(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

	virtual const sf::Vector2u getAnimationTexturePosition(Input) = 0;
	virtual std::unique_ptr<Inanimate> getAttack() = 0;

	void move() override;
	void updateGraphics(const sf::Time&);
	virtual void updateHitAnimation(const sf::Time&);
	void pushBack(const sf::Vector2f&);
	void addHitColor(sf::Color color);
	sf::Color getCurrentColor() const;
	sf::Color getBaseColor() const;
	void setAttacking(const bool& = false);

	bool isAttacking() const;
	bool isPushedBack() const;

	void setHp(int);
	int getHp() const;

protected:
	bool m_attacking;

private:
	int m_hp;
	sf::Clock m_pushbackTimer;
	bool m_isPushedback;
	sf::Vector2f m_collisionDirection;
	ColorAnimation m_hitAnimation;

};