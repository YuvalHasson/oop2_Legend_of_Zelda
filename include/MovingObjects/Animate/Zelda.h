#pragma once

#include "Enemy.h"
#include "MovementStrategy.h"
#include "PositionMovement.h"
#include "Standing.h"

class Zelda : public Enemy
{
public:
	Zelda(const sf::Texture&, const sf::Vector2f&);

	virtual sf::Vector2f getLinkPos() override { return sf::Vector2f(0, 0); };
	virtual std::unique_ptr<Inanimate> getAttack() override;
	virtual void update(const sf::Time&) override;
	virtual void updateHitAnimation(const sf::Time&) override {};
	virtual EnemyType getType() const override { return ZELDA; };
	virtual const sf::Vector2u getAnimationTexturePosition(Input) override { return ANIMATIONS_POSITIONS::Zelda; };

	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();

	void setActive(bool);
	void draw(sf::RenderTarget&) override;
	bool checkInnerCollision(const HitBox&) const;

private:
	static bool m_registerit;

	sf::Clock m_directionChangeClock;
	std::unique_ptr <MovementStrategy> m_moveStrategy;
	Input m_currInput;
	HitBox m_hitBox;
	sf::Text m_text;
	bool m_active;
};