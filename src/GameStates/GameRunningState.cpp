#include "GameRunningState.h"

GameRunningState::GameRunningState(sf::RenderWindow* window, std::vector<Board>&& board, sf::View&& view, Level level)
	:State(window), m_boardLevels(std::move(board)), m_view(std::move(view)),
	m_level(level), m_statusBar()
{
	StatusBar status(m_boardLevels[m_level].getLink().getHp(), m_boardLevels[m_level].getLink().getShooting());
	m_statusBar = status;
	setCenterView();
	std::cout << "GameRunningState\n";
}

void GameRunningState::update(const sf::Time& deltaTime)
{
	m_boardLevels[m_level].handleCollision();
	m_boardLevels[m_level].update(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		updateState(GAME_STATE::PAUSE_MENU);
	}
	m_statusBar.update(m_boardLevels[m_level].getLink().getHp(), m_boardLevels[m_level].getLink().getShooting());

	if (m_boardLevels[m_level].getLink().getHp() <= 0)
	{
		SoundResource::getSound().stopBackground(BACKGROUND_SOUND::StartGame);
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
		updateState(GAME_STATE::DEATH);
	}

	m_boardLevels[m_level].addProjectileToMoving();

	for (const auto& door : m_boardLevels[m_level].getDoors())
	{
		if (door->getChangeLevel())
		{
			m_nextLevel = door->getLevel();
			updateState(GAME_STATE::SWITCH_LEVEL);
			door->setChangeLevel(false);
		}
	}
}

void GameRunningState::render(sf::RenderTarget* target)
{
	setCenterView();
	
	if (!target)
	{
		target = getWindow();
	}
	target->setView(m_view);
	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() / 2.f, target->getView().getSize());
	m_boardLevels[m_level].draw(*target, viewBound);

	target->setView(target->getDefaultView());

	m_statusBar.setBottomView(*target);

	m_statusBar.draw(*target);
}

std::unique_ptr<State> GameRunningState::handleInput(const GAME_STATE& gameState)
{
	switch (gameState)
	{
	case GAME_STATE::MAIN_MENU:
		SoundResource::getSound().stopBackground(BACKGROUND_SOUND::StartGame);
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
		return std::make_unique<MainMenu>(getWindow());
	case GAME_STATE::EXIT:
		getWindow()->close();
		return nullptr;
	case GAME_STATE::PAUSE_MENU:
		return std::make_unique<PauseMenu>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level);
	case GAME_STATE::DEATH:
		return std::make_unique<DeathState>(getWindow(), m_boardLevels[m_level].getLink().getPosition(), std::move(m_view));
	case GAME_STATE::SWITCH_LEVEL:
		return std::make_unique<SwitchLevelState>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level, m_nextLevel);
	}
	return nullptr;
}

void GameRunningState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}

void GameRunningState::setCenterView()
{
	const float viewWidth = m_view.getSize().x;
	const float viewHeight = m_view.getSize().y;
	const float halfViewWidth = viewWidth / 2.f;
	const float halfViewHeight = viewHeight / 2.f;

	sf::Vector2f playerPos = m_boardLevels[m_level].getLink().getPosition();

	float viewCenterX = std::max(halfViewWidth, std::min(playerPos.x, Resources::getResource().getTexture(TEXTURE::Map)->getSize().x - halfViewWidth));
	float viewCenterY = std::max(halfViewHeight, std::min(playerPos.y, Resources::getResource().getTexture(TEXTURE::Map)->getSize().y - halfViewHeight));

	m_view.setCenter(viewCenterX, viewCenterY);
}
