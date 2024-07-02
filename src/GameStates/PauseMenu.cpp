#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, std::vector<Board>&& board, sf::View&& view, Level level)
	: State(window), m_boardLevels(std::move(board)), m_view(std::move(view)), m_volumeSlider(),
	m_pauseBackground(sf::Vector2f(WindowWidth * 1.2f, windowHeight / 1.3f)),
	m_controls(sf::Vector2f(WindowWidth / 2, windowHeight / 2)),
	m_level(level)
{
	setCenterView();
	getWindow()->setView(m_view);
	m_pauseBackground.setFillColor(sf::Color(128, 128, 128, 200));
	m_pauseBackground.setPosition(WindowWidth / 2.f - 750.f / 2.f , windowHeight / 2.f - 950.f / 2.f);
	m_controls.setTexture(Resources::getResource().getTexture(TEXTURE::Controls));
	m_controls.setPosition(WindowWidth / 1.5f, windowHeight / 7);

	add("Exit", std::make_unique<ExitButton>(this));
	add("Main Menu", std::make_unique<BackToMenuButton>(this));
	add("Resume", std::make_unique<BackToGameButton>(this));
	add("Save", std::make_unique<SaveButton>(this));
	m_options.back().second->setPosition(sf::Vector2f(70, 600));
	add("Load", std::make_unique<LoadButton>(this));
	m_options.back().second->setPosition(sf::Vector2f(70, 650));
}

void PauseMenu::update(const sf::Time&)
{
	for (const auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
	m_volumeSlider.update(*getWindow());
}

void PauseMenu::render(sf::RenderTarget* target)
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
	target->draw(m_pauseBackground);
	target->draw(m_controls);
	for (const auto& option : m_options)
	{
		option.second->draw(*target);
	}
	m_volumeSlider.draw(*target);

}

std::unique_ptr<State> PauseMenu::handleInput(const GAME_STATE& gameState)
{
	switch (gameState)
	{
	case GAME_STATE::MAIN_MENU:
		SoundResource::getSound().StopBackground();
		SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
		return std::make_unique<MainMenu>(getWindow());
	case GAME_STATE::EXIT:
		getWindow()->close();
		return nullptr;
	case GAME_STATE::GAME_RUNNING:
		SoundResource::getSound().playSound(SOUNDS::PauseMenuClose);
		return std::make_unique<GameRunningState>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level);
	case GAME_STATE::SAVE:
		return std::make_unique<SaveState>(getWindow(), std::move(m_boardLevels), std::move(m_view), m_level);
	case GAME_STATE::LOAD_GAME:
		return std::make_unique<LoadGameState>(getWindow(), GAME_STATE::PAUSE_MENU, std::move(m_boardLevels), std::move(m_view), m_level);

	}
	return nullptr;
}

void PauseMenu::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (const auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			updateState(GAME_STATE::GAME_RUNNING);
		}
	}
}

void PauseMenu::setCenterView()
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

void PauseMenu::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.emplace_back(std::make_pair(str, std::move(c)));
}
