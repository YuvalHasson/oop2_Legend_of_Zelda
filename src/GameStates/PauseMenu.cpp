#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, Board&& board, sf::View&& view, sf::Sprite background)
	: State(window), m_board(std::move(board)), m_view(std::move(view)), m_background(background), m_volumeSlider()
{
	setCenterView();
	getWindow()->setView(m_view);

	add("Exit", std::make_unique<ExitButton>(this));
	add("Main Menu", std::make_unique<BackToMenuButton>(this));
	add("Resume", std::make_unique<BackToGameButton>(this));
}

void PauseMenu::update(const sf::Time&)
{
	for (auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
	m_volumeSlider.update(*getWindow());
}

void PauseMenu::render(sf::RenderTarget* target)
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
	for (auto& option : m_options)
	{
		option.second->draw(*getWindow());
	}
	m_volumeSlider.draw(*getWindow());
}

std::unique_ptr<State> PauseMenu::handleInput(GAME_STATE gameState)
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
	case GAME_STATE::GAME_RUNNING:
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::StartGame);
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_board), std::move(m_view), m_background);
	}
	return nullptr;
}

void PauseMenu::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}
}

void PauseMenu::setCenterView()
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

void PauseMenu::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.emplace_back(std::make_pair(str, std::move(c)));
}
