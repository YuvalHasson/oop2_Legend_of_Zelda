#include "NewGameState.h"

NewGameState::NewGameState(sf::RenderWindow* window)
	:State(window), m_boardLevels(), m_view(sf::FloatRect(sf::Vector2f(80.f, 140.f), sf::Vector2f(250.f, 165.f)))
{
	setMap();
	m_view.setCenter(m_boardLevels[Level::Home].getLink().getPosition());
	SoundResource::getSound().StopBackground();
	SoundResource::getSound().playBackground(BACKGROUND_SOUND::House);
}

void NewGameState::update(const sf::Time& deltaTime)
{
	updateState(GAME_STATE::GAME_RUNNING);
}

void NewGameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);

	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() /2.f, target->getView().getSize());
	m_boardLevels[Level::Home].draw(*target, viewBound);
}

std::unique_ptr<State> NewGameState::handleInput(const GAME_STATE& gameState)
{
	if(gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (gameState == GAME_STATE::GAME_RUNNING)
	{
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), Level::Home);
	}
	else if(gameState == GAME_STATE::EXIT)
	{
		getWindow()->close();
	}
	return nullptr;
}

void NewGameState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}

void NewGameState::setMap()
{
	Board home;
	home.initializeLevel(Level::Home);
	home.makeLink();
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

	m_boardLevels.front().setLink(std::move(m_boardLevels.back().extractLink()));
}
