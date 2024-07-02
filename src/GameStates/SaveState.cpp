#include "SaveState.h"

SaveState::SaveState(sf::RenderWindow* window, std::vector<Board>&& board, sf::View&& view, Level level)
	:State(window), m_boardLevels(std::move(board)), m_view(std::move(view)), m_level(level)
{
	m_link = std::move(m_boardLevels[level].extractLink()); // Transfer ownership
	saveGame();
	m_boardLevels[m_level].setLink(std::move(m_link));
}

void SaveState::update(const sf::Time&)
{
	updateState(GAME_STATE::GAME_RUNNING);
}

void SaveState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);
}

std::unique_ptr<State> SaveState::handleInput(const GAME_STATE& gameState)
{
	if (gameState == GAME_STATE::GAME_RUNNING)
	{
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level);
	}
	else if (gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}
void SaveState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}

void SaveState::saveGame() const
{
	std::ofstream saveFile;
	saveFile.open("saveFile.txt");

	if (saveFile.is_open())
	{
		//---save link information---\\
		// Link position
		saveFile << m_link->getPosition().x << " " << m_link->getPosition().y << std::endl;
		// life
		saveFile << m_link->getHp() << std::endl;
		// Link weapons
		auto linkWeapons = m_link->getAllWeapons();
		// amount of weapons
		saveFile << linkWeapons.size() << std::endl;
		for (auto weapon : linkWeapons)
		{
			if (weapon == BowWeapon)
			{
				saveFile << BowWeapon << " ";
			}
			else if (weapon == SwordWeapon)
			{
				saveFile << SwordWeapon << " ";
			}
		}
		saveFile << std::endl;
		
		// score - currently not in use
		
		//---save level---\\
		// curr level
		saveFile << m_level << std::endl;

		// enemies positions
		auto enemiesPositions = m_boardLevels[m_level].getEnemiesPositions();
		// amount of enemies
		saveFile << enemiesPositions.size() << std::endl;
		for (const auto& enemy : enemiesPositions)
		{
			saveFile << enemy.second << " " << enemy.first.x << " " << enemy.first.y << std::endl;
		}
		// positions of boulders
		for (const auto& inanimateObject : m_boardLevels[m_level].getInanimateObjects())
		{
			if (const auto& p = dynamic_cast<Boulder*>(inanimateObject.get()))
			{
				saveFile << inanimateObject->getPosition().x << " " << inanimateObject->getPosition().y << std::endl;
			}
		}
		saveFile << "-1" << std::endl;
	}

}
