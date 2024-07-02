#pragma once

#include "Animate.h"

class Zelda : public Animate
{
public:
	Zelda(const sf::Texture&, const sf::Vector2f&);

	void update(const sf::Time&) override {};

	virtual std::unique_ptr<Inanimate> getAttack() override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };

	void setActive(bool);
	void draw(sf::RenderTarget&) override;
	bool getInnerBox(const HitBox&) const;
private:
	static bool m_registerit;

	HitBox m_hitBox;
	sf::Text m_text;
	bool m_active;
};