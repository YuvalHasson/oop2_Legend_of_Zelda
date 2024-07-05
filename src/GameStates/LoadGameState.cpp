#include "LoadGameState.h"

LoadGameState::LoadGameState(sf::RenderWindow* window, GAME_STATE state)
	: State(window), m_boardLevels(),
	m_view(sf::FloatRect(sf::Vector2f(80.f, 140.f), sf::Vector2f(250.f, 165.f))),
	m_cameFromState(state)
{
	initialize(window);
}

LoadGameState::LoadGameState(sf::RenderWindow* window, GAME_STATE state, std::vector<Board>&& board, sf::View&& view, Level level)
	: State(window), m_boardLevelsIfNoSave(std::move(board)), m_levelIfNoSave(level), m_cameFromState(state),
	m_view(view)
{
	initialize(window);
}

void LoadGameState::update(const sf::Time&)
{
	if (!m_isLoadFail)
	{
		updateState(GAME_STATE::GAME_RUNNING);
	}
	else {
		updateState(m_cameFromState);
	}
}

void LoadGameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);
}

std::unique_ptr<State> LoadGameState::handleInput(const GAME_STATE& gameState)
{
	switch (gameState)
	{
	case GAME_STATE::MAIN_MENU:
		return std::make_unique<MainMenu>(getWindow());
	case GAME_STATE::PAUSE_MENU:
		return std::make_unique<PauseMenu>(getWindow(), std::move(m_boardLevelsIfNoSave), std::move(m_view), m_levelIfNoSave);
	case GAME_STATE::GAME_OVER:
		return std::make_unique<GameOverState>(getWindow());
	case GAME_STATE::GAME_RUNNING:
		m_boardLevels[m_level].initializeLevel((Level)m_level);
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), (Level)m_level);
	}
	return nullptr;
}

void LoadGameState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}

void LoadGameState::updateLink()
{
	m_link->setPosition(m_linkPosition);
	m_link->setHp(m_linkLife);

	for (int index = 0; index < m_weaponIds.size(); index++)
	{
		if (m_weaponIds[index] == BowWeapon)
		{
			m_link->takeBow();
		}
		else if (m_weaponIds[index] == SwordWeapon)
		{
			m_link->takeSword();
		}
	}
}

void LoadGameState::updateLevel()
{	
	for (int index = 0; index < m_enemiesPositions.size(); index++)
	{
		
		if (m_enemiesPositions[index].second == PIG_WARRIOR)
		{
			if (auto p = Factory<Enemy>::instance()->create("PigWarrior", m_enemiesPositions[index].first))
			{
				m_enemyObjects.emplace_back(std::move(p));
			}
		}
		else if (m_enemiesPositions[index].second == OCTOROK)
		{
			if (auto p = Factory<Enemy>::instance()->create("Octorok", m_enemiesPositions[index].first))
			{
				m_enemyObjects.emplace_back(std::move(p));
			}
		}
		else if (m_enemiesPositions[index].second == SEA_URCHIN)
		{
			if (auto p = Factory<Enemy>::instance()->create("SeaUrchin", m_enemiesPositions[index].first))
			{
				m_enemyObjects.emplace_back(std::move(p));
			}
		}
		else if (m_enemiesPositions[index].second == WIZARDBOSS)
		{
			if (auto p = Factory<Enemy>::instance()->create("WizardBoss", m_enemiesPositions[index].first))
			{
				m_enemyObjects.emplace_back(std::move(p));
			}
		}
	}
	for (const auto& enemy : m_enemyObjects)
	{
		if (auto p = dynamic_cast<PigWarrior*>(enemy.get()))
		{
			p->registerAsLinkObserver(m_link.get());
		}
		if (auto p = dynamic_cast<WizardBoss*>(enemy.get()))
		{
			p->registerAsLinkObserver(m_link.get());
		}

	}
	m_inanimateObjects	= std::move(m_boardLevels[m_level].editInanimateObjects());
	m_staticObjects		= std::move(m_boardLevels[m_level].editStaticObjects());

	int index = 0;
	for (const auto& inanimateObject : m_inanimateObjects)
	{
		if (auto p = dynamic_cast<Boulder*>(inanimateObject.get()))
		{
			if (m_boulderPositions.size() > 0)
			{
				inanimateObject->setPosition(m_boulderPositions[index]);
				index++;
			}
		}
	}

	int indexInpots = 0;
	int indexInShrub = 0;
	for (const auto& destructibleObject : m_staticObjects)
	{
		if (auto p = dynamic_cast<Pot*>(destructibleObject.get()))
		{
			if (indexInpots >= m_potsPositions.size())
			{
				p->destroy();
			}
			else
			{
				if (m_potsPositions.size() > 0)
				{
					destructibleObject->setPosition(m_potsPositions[indexInpots]);
					indexInpots++;
				}
			}
		}
		else if (auto p1 = dynamic_cast<Shrub*>(destructibleObject.get()))
		{
			if (indexInShrub >= m_shrubPositions.size())
			{
				p1->destroy();
			}
			else
			{
				if (m_shrubPositions.size() > 0)
				{
					destructibleObject->setPosition(m_shrubPositions[indexInShrub]);
					indexInShrub++;
				}
			}
		}
	}

	m_boardLevels[m_level].setLink(std::move(m_link));
	m_boardLevels[m_level].setLoadedMap(m_enemyObjects, m_inanimateObjects, m_staticObjects);
}

void LoadGameState::setMap()
{
	Board home;
	home.initializeLevel(Level::Home);
	home.makeLink();
	// update Link before set maps
	m_link = std::move(home.extractLink());
	updateLink();
	// continue setting
	home.setLink(std::move(m_link));
	home.setMap();
	m_boardLevels.emplace_back(std::move(home));

	Board map;
	map.initializeLevel(Level::MAIN);
	map.setLink(std::move(m_boardLevels.back().extractLink()));
	map.setMap();
	m_boardLevels.emplace_back(std::move(map));

	Board dungeon1;
	dungeon1.setLink(std::move(m_boardLevels.back().extractLink()));
	dungeon1.initializeLevel(Level::FIRST_DUNGEON);
	dungeon1.setMap();
	m_boardLevels.emplace_back(std::move(dungeon1));

	Board dungeon2;
	dungeon2.setLink(std::move(m_boardLevels.back().extractLink()));
	dungeon2.initializeLevel(Level::SECOND_DUNGEON);
	dungeon2.setMap();
	m_boardLevels.emplace_back(std::move(dungeon2));

	Board dungeon3;
	dungeon3.setLink(std::move(m_boardLevels.back().extractLink()));
	dungeon3.initializeLevel(Level::BOSS_DUNGEON);
	dungeon3.setMap();
	m_boardLevels.emplace_back(std::move(dungeon3));

	Board dungeon4;
	dungeon4.setLink(std::move(m_boardLevels.back().extractLink()));
	dungeon4.initializeLevel(Level::THIERD_DUNGEON);
	dungeon4.setMap();
	m_boardLevels.emplace_back(std::move(dungeon4));

	m_link = std::move(m_boardLevels.back().extractLink());
}

void LoadGameState::loadGame(sf::RenderWindow* window)
{
	std::ifstream saveFile("saveFile.txt");
	try
	{
		if (saveFile.is_open())
		{
			try
			{
				m_isLoadFail = false;
				m_isGameLoad = true;
				int numOfWeapons;
				int numOfEnemies;
				
				//------read link information------\\
				
				// Link position
				saveFile >> m_linkPosition.x >> m_linkPosition.y;
				//handling bad Link position
				if (m_linkPosition.x < 16 || m_linkPosition.y < 16 || m_linkPosition.x > 790 || m_linkPosition.y > 500)
				{
					throw BadFileFormat();
				}
				// Link's lives
				saveFile >> m_linkLife;
				// Link weapons
				saveFile >> numOfWeapons;

				//handling bad numOfWeapons or bad life insertions
				if (numOfWeapons < 0 || numOfWeapons > 2 || m_linkLife < 1 || m_linkLife > MAX_HEALTH)
				{
					throw BadFileFormat();
				}
				for (int index = 0; index < numOfWeapons; index++)
				{
					int weaponId;
					saveFile >> weaponId;
					if (weaponId < 0 || weaponId > 2)
					{
						throw BadFileFormat();
					}
					m_weaponIds.emplace_back(weaponId);
				}

				//------load level------\\
				// level number
				saveFile >> m_level;
				//handling bad level insertions
				if (m_level < 0 || m_level > 5)
				{
					throw BadFileFormat();
				}

				// enemies positions
				saveFile >> numOfEnemies;
				//handling bad numOfEnemies insertions
				if (numOfEnemies < 0)
				{
					throw BadFileFormat();
				}
				for (int index = 0; index < numOfEnemies; index++)
				{
					float id, x, y;
					saveFile >> id >> x >> y;
					// handling bad enemies id or x or y insertions
					if (id < 0 || id > 4 || x < 0 || y < 0)
					{
						throw BadFileFormat();
					}
					m_enemiesPositions.emplace_back(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), EnemyType(id));
				}
				// read boulders positions
				float x = 0, y = 0;
				while (x != -1)
				{
					saveFile >> x;
					if (x == -1)
					{
						break;
					}
					saveFile >> y;
					// handling bad boulders x or y insertions
					if (x < 0 || y < 0)
					{
						throw BadFileFormat();
					}
					m_boulderPositions.emplace_back(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
				} 
				// read pots positions
				x = 0, y = 0;
				while (x != -2)
				{
					saveFile >> x;
					if (x == -2)
					{
						break;
					}
					saveFile >> y;
					// handling bad pots x or y insertions
					if (x < 0 || y < 0)
					{
						throw BadFileFormat();
					}
					m_potsPositions.emplace_back(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
				}

				// read shrub positions
				x = 0, y = 0;
				while (x != -3)
				{
					saveFile >> x;
					if (x == -3)
					{
						break;
					}
					saveFile >> y;
					// handling shrub x or y insertions
					if (x < 0 || y < 0)
					{
						throw BadFileFormat();
					}
					m_shrubPositions.emplace_back(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
				}

				//handle fail
				if (saveFile.fail())
				{
					throw BadFileFormat();
				}
			}
			catch (BadFileFormat& e)
			{
				m_isLoadFail = true;
				errorFileMsg(window, e.what());
			}
		}
		else
		{
			//cannot open file or BadFileName exception.
			throw BadFileName();
		}
	}
	catch (BadFileName& e)
	{
		m_isLoadFail = true;
		errorFileMsg(window, e.what());
	}
}

void LoadGameState::initialize(sf::RenderWindow* window)
{
	loadGame(window);
	if (!m_isLoadFail)
	{
		setMap();
		updateLevel();
	}
}

void LoadGameState::errorFileMsg(sf::RenderWindow* window, std::string msg)
{
	sf::Text errorTxt;
	errorTxt.setFont(*Resources::getResource().getFont());
	errorTxt.setString(msg);
	errorTxt.setStyle(sf::Text::Bold);
	errorTxt.setCharacterSize(50);
	errorTxt.setFillColor(sf::Color::Red);
	errorTxt.setPosition(sf::Vector2f(250.f, 280.f));

	sf::RectangleShape boxMsg;
	boxMsg.setFillColor(sf::Color::White);
	boxMsg.setSize(errorTxt.getGlobalBounds().getSize());
	boxMsg.setOutlineThickness(5);
	boxMsg.setOutlineColor(sf::Color::Black);
	boxMsg.setPosition(sf::Vector2f(250.f, 280.f));

	window->draw(boxMsg);
	window->draw(errorTxt);
	window->display();

	sf::sleep(sf::seconds(1));
	updateState(m_cameFromState);
}
