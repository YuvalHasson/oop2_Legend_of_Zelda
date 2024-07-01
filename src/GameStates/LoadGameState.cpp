#include "LoadGameState.h"

LoadGameState::LoadGameState(sf::RenderWindow* window)
	: State(window), m_boardLevels(), m_view(sf::FloatRect(sf::Vector2f(80.f, 140.f), sf::Vector2f(250.f, 165.f)))
{
	loadGame(window);
	setMap();
	updateLevel();
}

void LoadGameState::update(const sf::Time& deltaTime)
{
	updateState(GAME_STATE::GAME_RUNNING);
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
	if (gameState == GAME_STATE::GAME_RUNNING)
	{
		std::cout << "move to GAME_RUNNING\n";
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), Level(m_level));
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		std::cout << "EXIT\n";
		getWindow()->close();
	}
	return nullptr;
}
void LoadGameState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}

void LoadGameState::updateLink()
{
	m_link->getSprite().setPosition(m_linkPosition);
	m_link->setPosition(m_linkPosition);
	m_link->setHp(m_linkLife);

	for (int index = 0; index < m_weaponIds.size(); index++)
	{
		if (m_weaponIds[index] == BowWeapon)
		{
			m_link->takeBow();
			// need to understand how to destroy bowItem
		}
		else if (m_weaponIds[index] == SwordWeapon)
		{
			m_link->takeSword();
			// need to understand how to destroy swordItem
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
	}
	for (const auto& enemy : m_enemyObjects)
	{
		if (const auto& p = dynamic_cast<PigWarrior*>(enemy.get()))
		{
			p->registerAsLinkObserver(m_link.get());
		}

	}
	m_inanimateObjects = std::move(m_boardLevels[m_level].editInanimateObjects());

	int index = 0;
	for (auto& inanimateObject : m_inanimateObjects)
	{
		if (const auto& p = dynamic_cast<Boulder*>(inanimateObject.get()))
		{
			inanimateObject->getSprite().setPosition(m_boulderPositions[index]);
			inanimateObject->setPosition(m_boulderPositions[index]);
		}
		index++;
	}
	
	m_boardLevels[m_level].setLink(std::move(m_link));
	m_boardLevels[m_level].setLoadedMap(m_enemyObjects, m_inanimateObjects);
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
				
				//---read link information---\\
				// Link position
				saveFile >> m_linkPosition.x >> m_linkPosition.y;
				std::cout << m_linkPosition.x << " " << m_linkPosition.y << std::endl;
				// life
				saveFile >> m_linkLife;
				std::cout << m_linkLife << std::endl;

				// Link weapons
				saveFile >> numOfWeapons;
				std::cout << numOfWeapons << std::endl;
				for (int index = 0; index < numOfWeapons; index++)
				{
					saveFile >> m_weaponIds.emplace_back();
					std::cout << m_weaponIds[index] << " ";
				}
				std::cout << "\n" << "all good with link data\n";

				// score - currently not in use

				//---load level---\\
				// curr level
				saveFile >> m_level;
				std::cout << "m_level " << m_level << std::endl;
				// enemies positions
				saveFile >> numOfEnemies;
				std::cout << "numOfEnemies " << numOfEnemies << std::endl;
				for (int index = 0; index < numOfEnemies; index++)
				{
					int id, x, y;
					saveFile >> id >> x >> y;
					m_enemiesPositions.emplace_back(sf::Vector2f(x, y), EnemyType(id));
					std::cout << m_enemiesPositions[index].second << " " << m_enemiesPositions[index].first.x << " " << m_enemiesPositions[index].first.y << "\n";
				}
				int x = 0;
				int y = 0;
				while (x != -1)
				{
					saveFile >> x;
					if (x == -1)
					{
						break;
					}
					saveFile >> y;
					m_boulderPositions.emplace_back(sf::Vector2f(x, y));
				} 
				std::cout << "num of boulders: " << m_boulderPositions.size();
				std::cout << "\n" << "all good with level data\n";

				//handaling bad time insertions
				//if (m_loadGameTime < 0 || m_loadGameTime >(m_amntStickGenerated * 1.25))
				//{
				//	throw BadFileFormat();
				//}
				////handaling negative sticks
				//if (stickLeftToPick < 0 || m_amntStickGenerated < 0)
				//{
				//	throw BadFileFormat();
				//}

				//hadaling score
				//if (m_stickPoint < 0 || m_stickPoint > 5 * (m_amntStickGenerated - stickLeftToPick))
				//{
				//	throw BadFileFormat();
				//}

					////handle bad location
					//if (x < 300 || x > 650 || y < 250 || y > 700)
					//{
					//	throw BadFileFormat();
					//}
					////handle bad color
					//if (color < 1 || color > 5)
					//{
					//	throw BadFileFormat();
					//}

				//handale fail
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
			//cannot open file or BadFileName exeption.
			throw BadFileName();
		}
	}
	catch (BadFileName& e)
	{
		m_isLoadFail = true;
		errorFileMsg(window, e.what());
	}
}

void LoadGameState::errorFileMsg(sf::RenderWindow* window, std::string msg)
{
	sf::RectangleShape boxMsg;
	boxMsg.setSize(sf::Vector2f(440.f, 60.f));
	boxMsg.setFillColor(sf::Color::White);
	boxMsg.setOutlineThickness(5);
	boxMsg.setOutlineColor(sf::Color::Black);
	boxMsg.setPosition(sf::Vector2f(250.f, 280.f));

	sf::Text errorTxt;
	errorTxt.setFont(*Resources::getResource().getFont());
	errorTxt.setString(msg);
	errorTxt.setStyle(sf::Text::Bold);
	errorTxt.setCharacterSize(50);
	errorTxt.setFillColor(sf::Color::Red);
	errorTxt.setPosition(sf::Vector2f(250.f, 280.f));

	window->draw(boxMsg);
	window->draw(errorTxt);
	window->display();

	sf::sleep(sf::seconds(1));
	std::cout << "byeeee\n";
	updateState(GAME_STATE::MAIN_MENU);
}
