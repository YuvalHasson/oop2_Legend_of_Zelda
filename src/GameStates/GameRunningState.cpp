#include "GameRunningState.h"

GameRunningState::GameRunningState(sf::RenderWindow* window, Board&& board, sf::View&& view, sf::Sprite background)
	:State(window), m_board(std::move(board)), m_view(std::move(view)), m_background(background)
{
	const float viewWidth = m_view.getSize().x;
	const float viewHeight = m_view.getSize().y;
	const float halfViewWidth = viewWidth / 2.f;
	const float halfViewHeight = viewHeight / 2.f;
	
	sf::Vector2f playerPos = m_board.getSprite(0).getPosition();

	float viewCenterX = std::max(halfViewWidth, std::min(playerPos.x, Resources::getResource().getTexture(TEXTURE::Map)->getSize().x - halfViewWidth));
	float viewCenterY = std::max(halfViewHeight, std::min(playerPos.y, Resources::getResource().getTexture(TEXTURE::Map)->getSize().y - halfViewHeight));
	
	m_view.setCenter(viewCenterX, viewCenterY);
}

void GameRunningState::update(const sf::Time& deltaTime)
{
	m_board.move(deltaTime);
	m_board.handleCollision();
	m_board.update(deltaTime);
}

void GameRunningState::render(sf::RenderTarget* target)
{
	getWindow()->setView(m_view);
	
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_background);
	sf::FloatRect viewBound(target->getView().getCenter() - target->getView().getSize() / 2.f, target->getView().getSize());
	m_board.draw(*getWindow(), viewBound);
}

std::unique_ptr<State> GameRunningState::handleInput(GAME_STATE)
{
	if (getGameState() == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	else if (getGameState() == GAME_STATE::EXIT)
	{
		getWindow()->close();
		return nullptr;
	}
	return std::make_unique<GameRunningState>(getWindow(), std::move(m_board), std::move(m_view), m_background);
}

void GameRunningState::buttonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&)
{

}
