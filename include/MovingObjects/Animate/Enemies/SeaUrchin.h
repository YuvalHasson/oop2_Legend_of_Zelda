#pragma once

#include "Enemy.h"

class SeaUrchin : public Enemy
{
public:
	SeaUrchin(const sf::Texture& texture, const sf::Vector2f& position);
	virtual sf::Vector2f getLinkPos() override;
	virtual std::unique_ptr<Inanimate> getAttack() override;
	virtual void update(const sf::Time& deltaTime) override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override;
	//virtual bool switchHitBox(bool) { return false; };
	//virtual void updateLineOfSight() override {};

private:
	static bool m_registerit;
};