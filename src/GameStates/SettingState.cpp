#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window)
	: State(window)
{
	m_menuBackground.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_menuBackground.setTexture(Resources::getResource().getTexture(TEXTURE::Menu));

	add("Back", std::make_unique<BackButton>(this));
	add("Volume Down", std::make_unique<VolumeDownButton>());
	add("Volume Up", std::make_unique<VolumeUpButton>());
}

void SettingState::update(const sf::Time& deltaTime)
{
	for (auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_menuBackground);
	for (auto& option : m_options)
	{
		option.second->draw(*getWindow());
	}
}

std::unique_ptr<State> SettingState::handleInput(GAME_STATE gameState)
{
	if(gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	return std::make_unique<SettingState>(getWindow());
}

void SettingState::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (auto& option : m_options)
	{
		if (option.second->isButtonPressed(window, event.mouseButton))
		{
			option.second->execute();
		}
	}
}

void SettingState::add(const std::string& str, std::unique_ptr<Button> c)
{
	m_options.push_back(std::make_pair(str, std::move(c)));
}
