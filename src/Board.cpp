#include "Board.h"
#include "Sword.h"
#include "Boulder.h"

#include <iostream> // debug

Board::Board() {}

Board::Board(Board&& other) noexcept
	: m_movingObjects(std::move(other.m_movingObjects)), m_staticObjects(std::move(other.m_staticObjects)),
	  m_link(std::move(other.m_link)) {}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other)
	{
		m_movingObjects = std::move(other.m_movingObjects);
		m_staticObjects = std::move(other.m_staticObjects);
		m_link = std::move(other.m_link);
	}
	return *this;
}

void Board::draw(sf::RenderTarget& target, sf::FloatRect& viewBound)
{
	for (const auto& gameObject : m_staticObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(target);
		}
	}

	for (auto& gameObject : m_movingObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(target);
		}
  	}
	m_link->draw(target);
}

void Board::addProjectileToMoving()
{
	std::vector<std::unique_ptr<MovingObjects>> newProjectiles;

    for (const auto& moving : m_movingObjects)
    {
        auto projectile = moving->getAttack();
        if (projectile)
        {
            newProjectiles.emplace_back(std::move(projectile));
        }
    }
	auto linkArrow = m_link->getAttack();
	if(linkArrow){
		newProjectiles.emplace_back(std::move(linkArrow));
	}
    m_movingObjects.insert(m_movingObjects.end(), std::make_move_iterator(newProjectiles.begin()), std::make_move_iterator(newProjectiles.end()));
}

void Board::makeLink()
{	
	if (auto p = Factory<Link>::instance()->create("Link", { 32.f, 50.f }))
	{
		m_link = std::move(p);
	}
}

void Board::move(const sf::Time&) {}

void Board::update(const sf::Time& deltaTime)
{
	for (auto& gameObject : m_movingObjects)
	{
		gameObject->update(deltaTime);
	}

	m_link->update(deltaTime);

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
	std::erase_if(m_movingObjects, [](const auto& MovingObjects) { return MovingObjects->isDestroyed(); });
}

void Board::handleCollision()
{
	try
	{
		//if link is attacking get the sword from link and check its collision with enemies
		Sword* sword = m_link->getSword();


		//link and static objects
		for (const auto& staticObject : m_staticObjects)
		{	
			if(sword){
				if (colide(*sword, *staticObject))
				{
					processCollision(*sword, *staticObject);
				}
			}
			if (colide(*m_link, *staticObject))
			{
				processCollision(*m_link, *staticObject);
			}
		}

		//link, sword and moving objects
		for (const auto& movingObject : m_movingObjects)
		{
			if(sword){
				if (colide(*sword, *movingObject))
				{
					processCollision(*sword, *movingObject);
				}
			}
			if (colide(*m_link, *movingObject))
			{
				processCollision(*m_link, *movingObject);
			}
		}

		//moving and static objects
		for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) {
				processCollision(*obj1, *obj2);
			}
			});

		for_each_pair(m_movingObjects.begin(), m_movingObjects.end(), [this](auto& obj1, auto& obj2) {
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
	m_movingObjects = std::move(m_map.getEnemyObjects(m_link.get()));
	m_staticObjects = std::move(m_map.getStaticObjects());

	//auto boulders = Factory::createBoulder();
	//m_movingObjects.insert(m_movingObjects.end(), std::make_move_iterator(boulders.begin()), std::make_move_iterator(boulders.end()));
}

bool Board::isAttacking() const
{
	for (const auto& moving : m_movingObjects)
	{
		if (moving->isAttacking())
		{
			moving->setAttacking(false);
			return true;
		}
	}
	return false;
}
