#pragma once

#include "Enemy.h"

class SeaUrchin : public Enemy
{
public:
	SeaUrchin(const sf::Texture&, const sf::Vector2f&);
	virtual sf::Vector2f getLinkPos() override;
	virtual std::unique_ptr<Inanimate> getAttack() override;
	virtual void update(const sf::Time&) override;
	virtual const sf::Vector2u getAnimationTexturePosition(Input) override;
	virtual EnemyType getType() const override;

private:
	static bool m_registerit;
};