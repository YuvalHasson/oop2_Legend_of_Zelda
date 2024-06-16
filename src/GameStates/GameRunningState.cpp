#include "GameRunningState.h"

GameRunningState::GameRunningState(sf::RenderWindow* window, Board&& board, sf::View&& view, sf::Sprite background)
	:State(window), m_board(std::move(board)), m_view(std::move(view)), m_background(background),
	m_statusBar(board.getSprite().getHp())
{
	setCenterView();
}

void GameRunningState::update(const sf::Time& deltaTime)
{
	m_board.move(deltaTime);
	m_board.handleCollision();
	m_board.update(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		updateState(GAME_STATE::PAUSE_MENU);
	}
	m_statusBar.update(m_board.getSprite().getHp());

	if (m_board.getSprite().getHp() <= 0)
	{
		SoundResource::getSound().stopBackground(BACKGROUND_SOUND::StartGame);
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
		updateState(GAME_STATE::MAIN_MENU);
	}
}

void GameRunningState::render(sf::RenderTarget* target)
{
	setCenterView();

	getWindow()->setView(m_view);
	
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_background);
	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() / 2.f, target->getView().getSize());
	m_board.draw(*getWindow(), viewBound);

	getWindow()->setView(getWindow()->getDefaultView());

	m_statusBar.setBottomView(*getWindow());

	m_statusBar.draw(*getWindow());
}

std::unique_ptr<State> GameRunningState::handleInput(GAME_STATE gameState)
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
		return std::make_unique<PauseMenu>(getWindow(), std::move(m_board), std::move(m_view), m_background);
	}
	return nullptr;
}

void GameRunningState::buttonPressed(sf::RenderWindow&, const sf::Event&)
{

}

void GameRunningState::setCenterView()
{
	const float viewWidth = m_view.getSize().x;
	const float viewHeight = m_view.getSize().y;
	const float halfViewWidth = viewWidth / 2.f;
	const float halfViewHeight = viewHeight / 2.f;

	sf::Vector2f playerPos = m_board.getSprite().getPosition();

	float viewCenterX = std::max(halfViewWidth, std::min(playerPos.x, Resources::getResource().getTexture(TEXTURE::Map)->getSize().x - halfViewWidth));
	float viewCenterY = std::max(halfViewHeight, std::min(playerPos.y, Resources::getResource().getTexture(TEXTURE::Map)->getSize().y - halfViewHeight));

	m_view.setCenter(viewCenterX, viewCenterY);
}
