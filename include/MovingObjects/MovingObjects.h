#pragma once

#include "GameObject.h"
#include "Misc/Animation.h"

const sf::Time pushbackDuration(sf::seconds(0.2f));

class MovingObjects : public GameObject
{
public:
	MovingObjects(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

	virtual void move();
	virtual void update(const sf::Time& deltaTime) = 0;
	// virtual void attack(const sf::Time& deltaTime) = 0;
	virtual void handleCollision() = 0;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) = 0;
	virtual std::unique_ptr<MovingObjects> getAttack();

	void updateSprite();
	void setGraphics(const sf::Vector2u&, int, bool = false, bool = false, float switchTime = 0.2f);
	void setSpeed(int);
	void updateGraphics(const sf::Time& deltaTime);
	void setDirection(const sf::Vector2i&);
	void setAttacking(bool = false);
	void undoMove();
	void pushBack();

	sf::Vector2i getDirection() const;

	bool isAnimationDone() const;
	bool isAttacking() const;
	bool isPushedBack()const;

	void setHp(int);
	int getHp()const;

protected:
	bool m_attacking; //might not be necessary

private:
	Animation m_animation;
	sf::Vector2i m_direction;
	int m_speed;
	int m_hp;
	sf::Clock m_pushbackTimer;
	bool m_isPushedback;
	

};