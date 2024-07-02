#pragma once

#include "Weapon.h"

class EnemySword : public Weapon
{
public:
	EnemySword(const sf::Texture&, const sf::Vector2f&);

	virtual void update(const sf::Time&) override;
	virtual void setBool()override;

private:
	static bool m_registerit;
	sf::Clock m_startTime;
	bool m_enemyInSmartMove;
};