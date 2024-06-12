#include "Controller.h"
#include <iostream> //for debugging

Controller::Controller()
	: m_window(sf::VideoMode(windowHeight, WindowWidth), "Zelda", sf::Style::Close | sf::Style::Titlebar) ,
    m_state(std::make_unique<MainMenu>(&m_window))
{
	m_window.setFramerateLimit(60);
	m_window.setIcon(Resources::getResource().getIcon()->getSize().x, Resources::getResource().getIcon()->getSize().y, Resources::getResource().getIcon()->getPixelsPtr());
    SoundResource::getSound().playBackground(BACKGROUND_SOUND::Menu);
}

Controller::~Controller()
{
}

void Controller::run()
{
    sf::Clock clock;
    sf::Time deltaTime;
    while (m_window.isOpen())
    {
        deltaTime = clock.restart();
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
				m_state->buttonPressed(*m_state->getWindow(), event);
				break;
            default:
                break;
            }
        }

        std::unique_ptr<State> state = m_state->handleInput(m_state->getGameState());
        if (state)
        {
            m_state = std::move(state);
            m_state->update(deltaTime);
        }
        m_window.clear();
        m_state->render();
        m_window.display();
    }
}
