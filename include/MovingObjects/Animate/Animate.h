#pragma once

#include "MovingObjects.h"

#include "Inanimate/Inanimate.h"

const sf::Time pushbackDuration(sf::seconds(0.2f));

class Animate : public MovingObjects
{
public:
	Animate(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

	virtual const sf::Vector2u& getAnimationTexturePosition(Input) = 0;
	virtual std::unique_ptr<Inanimate> getAttack() = 0;

	void move() override;
	void updateGraphics(const sf::Time& deltaTime);
	void setAttacking(const bool& = false);
	void pushBack(const sf::Vector2i&);

	bool isAttacking() const;
	bool isPushedBack() const;

	void setHp(int);
	int getHp() const;

protected:
	bool m_attacking; //might not be necessary

private:
	int m_hp;
	sf::Clock m_pushbackTimer;
	bool m_isPushedback;
	sf::Vector2i m_collisionDirection;

};