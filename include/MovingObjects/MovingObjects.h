#pragma once

#include "GameObject.h"
#include "Misc/Animation.h"

class MovingObjects : public GameObject
{
public:
	MovingObjects(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);

	virtual void move();
	virtual void update(const sf::Time& deltaTime) = 0;
	
	void updateSprite();
	void setGraphics(const sf::Vector2u&, int, bool = false, float switchTime = 0.2f);
	void setSpeed(float);
	void setDirection(const sf::Vector2i&);
	void undoMove();

	sf::Vector2i getDirection() const;

protected:
	Animation& getAnimation();
	float getSpeed() const;

private:
	Animation m_animation;
	sf::Vector2i m_direction;
	float m_speed;
};