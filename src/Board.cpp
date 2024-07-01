#include "Board.h"
#include "Sword.h"
#include "Shield.h"
#include "Boulder.h"

#include <iostream> // debug

std::vector<sf::FloatRect> Board::m_staticRects;

Board::Board() {}

Board::Board(Board&& other) noexcept
	:m_enemiesObjects(std::move(other.m_enemiesObjects)),
	 m_inanimateObjects(std::move(other.m_inanimateObjects)),
	 m_staticObjects(std::move(other.m_staticObjects)),
	 m_staticRectsOfCurLevel(std::move(other.m_staticRectsOfCurLevel)),
	 m_doors(std::move(other.m_doors)),
	 m_zelda(std::move(other.m_zelda)),
	 m_link(std::move(other.m_link)),
	 m_background(std::move(other.m_background)) {}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other)
	{
		m_enemiesObjects	= std::move(other.m_enemiesObjects);
		m_inanimateObjects	= std::move(other.m_inanimateObjects);
		m_staticObjects		= std::move(other.m_staticObjects);
		m_link				= std::move(other.m_link);
		m_zelda				= std::move(other.m_zelda);
		m_background		= std::move(other.m_background);
		m_doors				= std::move(other.m_doors);
	}
	return *this;
}

void Board::draw(sf::RenderTarget& target, sf::FloatRect& viewBound)
{
	target.draw(m_background);

	for (const auto& gameObject : m_enemiesObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(target);
		}
  	}

	for (const auto& gameObject : m_inanimateObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(target);
		}
	}

	for (const auto& gameObject : m_staticObjects)
	{
		if (gameObject->getSprite().getGlobalBounds().intersects(viewBound))
		{
			gameObject->draw(target);
		}
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(16,16));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setOutlineThickness(1);
	for (const auto& gameObject : m_staticRects)
	{
		rect.setPosition(gameObject.left, gameObject.top);
		//target.draw(rect);
	}

	if (m_zelda)
	{
		m_zelda->draw(target);
	}
	m_link->draw(target);
}

void Board::addProjectileToMoving()
{
    for (const auto& moving : m_enemiesObjects)
    {
        auto projectile = moving->getAttack();
        if (projectile)
        {
            m_inanimateObjects.emplace_back(std::move(projectile));
        }
    }
	auto linkArrow = m_link->getAttack();
	if(linkArrow)
	{
		m_inanimateObjects.emplace_back(std::move(linkArrow));
	}
}

void Board::makeLink()
{	
	if (auto p = Factory<Link>::instance()->create("Link", { 86.f, 35.f }))
	{
		m_link = std::move(p);
	}

	if (auto p = Factory<Zelda>::instance()->create("Zelda", { 120.f, 35.f }))
	{
		m_zelda = std::move(p);
	}
}

void Board::update(const sf::Time& deltaTime)
{
	for (const auto& gameObject : m_inanimateObjects)
	{
		gameObject->update(deltaTime);
	}
	for (const auto& gameObject : m_enemiesObjects)
	{
		gameObject->update(deltaTime);
	}

	m_link->update(deltaTime);

	std::erase_if(m_staticObjects, [](const auto& StaticObejects) { return StaticObejects->isDestroyed(); });
	std::erase_if(m_enemiesObjects, [](const auto& MovingObejects) { return MovingObejects->isDestroyed(); });
	std::erase_if(m_inanimateObjects, [](const auto& InanimateObejects) { return InanimateObejects->isDestroyed(); });
	
	m_enemiesPositions.clear();
	for (const auto& enemy : m_enemiesObjects)
	{
		m_enemiesPositions.emplace_back(enemy->getPosition(), enemy->getType());
	}
}

void Board::handleCollision()
{
	try
	{
		//if link is attacking get the sword from link and check its collision with enemies
		Sword* sword	= m_link->getSword();
		Shield* shield	= m_link->getShield();


		//link and static objects
		for (const auto& staticObject : m_staticObjects)
		{	
			if(sword)
			{
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
		for (const auto& movingObject : m_enemiesObjects)
		{
			if(sword)
			{
				if (colide(*sword, *movingObject))
				{
					processCollision(*sword, *movingObject);
				}
			}
			if(shield){
				if (colide(*shield, *movingObject))
				{
					processCollision(*shield, *movingObject);
				}
			}
			if (colide(*m_link, *movingObject))
			{
				processCollision(*m_link, *movingObject);
			}
		}

		//link, sword and inanimate objects
		for(const auto& object : m_inanimateObjects)
		{
			if (sword)
			{
				if (colide(*sword, *object))
				{
					processCollision(*sword, *object);
				}
			}
			
			if (shield) {
				if (colide(*shield, *object))
				{
					processCollision(*shield, *object);
				}
			}
			if (colide(*m_link, *object))
			{
				processCollision(*m_link, *object);
			}
		}

		if (m_zelda)
		{
			if (colide(*m_link, *m_zelda))
			{
				processCollision(*m_link, *m_zelda);
			}
		}

		//link and doors
		for (const auto& door : m_doors)
		{
			if (colide(*m_link, *door))
			{
				processCollision(*m_link, *door);
			}
		}

		//moving and static objects
		for_each_pair(m_enemiesObjects.begin(), m_enemiesObjects.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2)) 
			{
				processCollision(*obj1, *obj2);
			}
			});

		//moving and inanimate objects
		for_each_pair(m_inanimateObjects.begin(), m_inanimateObjects.end(), m_staticObjects.begin(), m_staticObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2))
			{
				processCollision(*obj1, *obj2);
			}
			});

		for_each_pair(m_enemiesObjects.begin(), m_enemiesObjects.end(), m_inanimateObjects.begin(), m_inanimateObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2))
			{
				processCollision(*obj1, *obj2);
			}
			});

		for_each_pair(m_enemiesObjects.begin(), m_enemiesObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2))
			{
				processCollision(*obj1, *obj2);
			}
			});

		//inanimate objects
		for_each_pair(m_inanimateObjects.begin(), m_inanimateObjects.end(), [this](auto& obj1, auto& obj2) {
			if (colide(*obj1, *obj2))
			{
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
	m_enemiesObjects	= std::move(m_map.getEnemyObjects(m_link.get()));
	m_staticObjects		= std::move(m_map.getStaticObjects(m_link.get()));
	m_inanimateObjects	= std::move(m_map.getInanimateObjects());
	m_doors				= std::move(m_map.getDoors());

}

void Board::setLoadedMap(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Inanimate>>& inanimateObjects)
{
	m_staticRects		= m_staticRectsOfCurLevel;
	m_enemiesObjects.clear();

	m_enemiesObjects	= std::move(enemies);
	m_inanimateObjects	= std::move(inanimateObjects);
}

void Board::initializeLevel(const Level& level)
{
	SoundResource::getSound().StopBackground();
	switch (level)
	{
	case Level::Home:
		m_map.setMap("Home.csv");
		m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Home));
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::House);
		break;
	case Level::MAIN:
		m_map.setMap("Map.csv");
		m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Map));
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::OverWorld);
		break;
	case Level::FIRST_DUNGEON:
		m_map.setMap("Dungeon.csv");
		m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Dungeon1));
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Dungeon01);
		break;
	case Level::SECOND_DUNGEON:
		m_map.setMap("Dungeon01.csv");
		m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::Dungeon2));
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Dungeon01);
		break;
	case Level::BOSS_DUNGEON:
		m_map.setMap("BossDungeon.csv");
		m_background.setTexture(*Resources::getResource().getTexture(TEXTURE::BossDungeon));
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Dungeon01);
		break;
	}
	m_staticRects = m_map.getStaticObjectsRects();
	m_staticRectsOfCurLevel = m_staticRects;
}

void Board::resetEnemiesAndInanimated()
{
	m_enemiesObjects = std::move(m_map.getEnemyObjects(m_link.get()));
	m_inanimateObjects = std::move(m_map.getInanimateObjects());
}

std::vector<std::pair<sf::Vector2f, EnemyType>> Board::getEnemiesPositions() const
{
	return m_enemiesPositions;
}

const std::vector<std::unique_ptr<Inanimate>>& Board::getInanimateObjects() const
{
	return m_inanimateObjects;
}

std::vector<std::unique_ptr<Inanimate>>& Board::editInanimateObjects()
{
	return m_inanimateObjects;
}

std::vector<sf::FloatRect> Board::getStaticRectsOfCurLevel() const
{
	return m_staticRectsOfCurLevel;
}

bool Board::isAttacking() const
{
	for (const auto& moving : m_enemiesObjects)
	{
		if (moving->isAttacking())
		{
			moving->setAttacking(false);
			return true;
		}
	}
	return false;
}

const sf::Sprite& Board::getBackground() const
{
	return m_background;
}

std::vector<sf::FloatRect> Board::getStaticRects(){
	return m_staticRects;
}