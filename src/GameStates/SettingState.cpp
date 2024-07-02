#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window)
	: State(window), m_volumeSlider()
{
	m_menuBackground.setSize(sf::Vector2f(windowHeight, WindowWidth));
	m_menuBackground.setTexture(Resources::getResource().getTexture(TEXTURE::Menu));

	add("Back", std::make_unique<BackToMenuButton>(this));
}

void SettingState::update(const sf::Time&)
{
	for (const auto& option : m_options)
	{
		option.second->overButton(*getWindow());
	}
	m_volumeSlider.update(*getWindow());
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_menuBackground);
	for (const auto& option : m_options)
	{
		option.second->draw(*target);
	}
	m_volumeSlider.draw(*target);
}

std::unique_ptr<State> SettingState::handleInput(const GAME_STATE& gameState)
{
	if(gameState == GAME_STATE::MAIN_MENU)
	{
		return std::make_unique<MainMenu>(getWindow());
	}
	return nullptr;
}

void SettingState::buttonPressed(sf::RenderWindow& window, const sf::Event& event)
{
	for (const auto& option : m_options)
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
