#include "Board.h"
#include "Sword.h"

#include <iostream> // debug

Board::Board()
{
}

Board::Board(Board&& other) noexcept
	: m_movingObjects(std::move(other.m_movingObjects)), m_enemies(std::move(other.m_enemies))
	,m_staticObjects(std::move(other.m_staticObjects)), m_link(std::move(other.m_link))
{
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other)
	{
		m_movingObjects = std::move(other.m_movingObjects);
		m_enemies = std::move(other.m_enemies);
		m_staticObjects = std::move(other.m_staticObjects);
		m_link = std::move(other.m_link);
	}
	return *this;
}

void Board::draw(sf::RenderWindow& window, sf::FloatRect& viewBound)
{
	for (const auto& gameObject : m_staticObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(window);
		}
	}

	for (const auto& enemy : m_enemies)

	{
		if (enemy->getSprite().getGlobalBounds().intersects(viewBound))
		{
			enemy->draw(window);
		}
	}
	for (auto& gameObject : m_movingObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
			gameObject->draw(window);
  	}
	m_link->draw(window);
}

void Board::addProjectileToMoving()
{
	for (const auto& enemy : m_enemies)
	{
		auto projectile = enemy->getAttack();
		if (projectile)
		{
			m_movingObjects.emplace_back(std::move(projectile));
		}
		// not supposed to be here - maybe in a function
		if (dynamic_cast<PigWarrior*>(enemy.get()))
		{
			auto sword = Factory::createSword();
			dynamic_cast<PigWarrior*>(enemy.get())->insertSword(sword.get());
			m_movingObjects.emplace_back(std::move(sword));
		}
	}

}

void Board::makeLink()
{	
	auto sword = Factory::createSword();
	m_link = Factory::createLink();
	m_link->insertSword(sword.get());
	m_movingObjects.emplace_back(std::move(sword));
}

void Board::move(const sf::Time& deltaTime)
{
	//for (auto& gameObject : m_movingObjects)
	//{
	//	// gameObject->move(deltaTime);
	//	// gameObject->attack(deltaTime); //might need to be somewhere else
	//}
}

void Board::update(const sf::Time& deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		enemy->update(deltaTime);
	}
	for (auto& gameObject : m_movingObjects)
	{
		gameObject->update(deltaTime);
		//if (dynamic_cast<Link*>(gameObject.get()))
		//{
		//	for (auto& otherGameObject : m_movingObjects)
		//	{
		//		if (dynamic_cast<PigWarrior*>(otherGameObject.get()))
		//		{
		//			PigWarrior* PigWarriorPtr = dynamic_cast<PigWarrior*>(otherGameObject.get());
		//			PigWarriorPtr->UpdateLinkPos(gameObject.get()->getSprite().getPosition());
		//		}
		//	}
		//}
	}

	m_link->update(deltaTime);

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
	std::erase_if(m_movingObjects, [](const auto& MovingObejects) { return MovingObejects->isDestroyed(); });
	std::erase_if(m_enemies, [](const auto& enemy) { return enemy->isDestroyed(); });
}

void Board::handleCollision()
{
	try
	{
		//link and static objects
		for (const auto& staticObjects : m_staticObjects)
		{
			if (colide(*m_link, *staticObjects))
			{
				processCollision(*m_link, *staticObjects);
			}
		}
		//link and enemies
		for (const auto& enemy : m_enemies)
		{
			if (colide(*m_link, *enemy))
			{
				processCollision(*m_link, *enemy);
			}
			for(const auto& moving : m_movingObjects)
			{
				if (colide(*moving, *enemy))
				{
					processCollision(*moving, *enemy);
				}
			}
		}
		
		//link and moving objects
		for (const auto& movingObjects : m_movingObjects)
		{
			if (colide(*m_link, *movingObjects))
			{
				processCollision(*m_link, *movingObjects);
			}
		}

		// Handle collisions among moving objects
		for_each_pair(m_enemies.begin(), m_enemies.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});

		// Handle collisions between moving and static objects
		for_each_pair(m_enemies.begin(), m_enemies.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});

		for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Board::setMap()
{
	m_enemies = std::move(m_map.getEnemyObjects());
	m_staticObjects = std::move(m_map.getStaticObjects());
}

bool Board::isAttacking() const
{
	for (const auto& enemy : m_enemies)
	{
		if (enemy->isAttacking())
		{
			enemy->setAttacking(false);
			return true;
		}
	}
	return false;
}
