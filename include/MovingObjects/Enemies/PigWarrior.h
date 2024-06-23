#pragma once

#include "Enemy.h"

#include "MovementStrategy.h"
#include "SmartMovement.h"
#include "PatrolMovement.h"
//#include "AttackingState.h"
#include "Sword.h"
#include "LinkObserver.h"

#include "Link.h"

//const sf::Time invincibilityTime(sf::seconds(2));

class PigWarrior : public Enemy, public LinkObserver
{
public:
	PigWarrior(const sf::Texture& texture, const sf::Vector2f& position);
	~PigWarrior();

	virtual void update(const sf::Time& deltaTime) override;
	virtual void handleCollision() override;
	virtual void attack();
	virtual void draw(sf::RenderTarget&) override;
	virtual const sf::Vector2u& getAnimationTexturePosition(Input)override;
	void setMoveStrategy(std::unique_ptr<MovementStrategy>&);
	void setMoveStrategy(std::unique_ptr<MovementStrategy>);
	void PerformMove();
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	virtual void updateLinkPosition(const sf::Vector2f& position)override;

	virtual std::unique_ptr<MovingObjects> getAttack() override;

	void registerAsLinkObserver(Link*);
	void UpdateLinkPos(const sf::Vector2f& position);
	//void setBoardPtr(Board*);

	void insertSword(Sword*);
	Sword* getSword();

	void swipeSword();
	void stopSwordSwipe();

	bool getInvincible()const;
	void initializeInvincible();

private:
	sf::Clock m_directionChangeClock;
	Input m_currInput;

	std::unique_ptr <MovementStrategy> m_moveStrategy;
	sf::Vector2f m_linkPos;
	Link * m_link;

	static bool m_registerit;
	std::unique_ptr<Sword> m_sword;

	sf::Clock m_invincibleTimer;

	//for (const auto& enemy : m_movingObjects)
	//{
	//	if (dynamic_cast<PigWarrior*>(enemy.get()))
	//	{
	//		std::cout << "addSword\n";
	//		auto sword = Factory::createSword();
	//		dynamic_cast<PigWarrior*>(enemy.get())->insertSword(sword.get());
	//		//m_movingObjects.emplace_back(std::move(sword));
	//	}
	//}
};

