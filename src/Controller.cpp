#include "Controller.h"

Controller::Controller()
	: m_window(sf::VideoMode(windowHeight, WindowWidth), "Zelda", sf::Style::Close | sf::Style::Titlebar)
{
	m_window.setFramerateLimit(60);
    m_gameState = GAME_STATE::MAIN_MENU;
}

Controller::~Controller()
{
}

void Controller::run()
{
    sf::RectangleShape player(sf::Vector2f(25, 25));
    player.setTexture(Resources::getResource().getTexture(TEXTURE::Score));
    player.setPosition(100, 100);
    player.setOrigin(25 / 2, 25 / 2);

    sf::RectangleShape background(sf::Vector2f(windowHeight, WindowWidth));
    background.setTexture(Resources::getResource().getTexture(TEXTURE::Map));

    sf::View view(sf::FloatRect(sf::Vector2f(80, 140), sf::Vector2f(250, 265)));
    view.setCenter(player.getPosition());

    sf::Time deltaTime = sf::seconds(1.f / 60.f);

    while (m_window.isOpen())
    {
        if (m_gameState == GAME_STATE::NEW_GAME)
        {
            m_gameState = GAME_STATE::GAME_RUNNING;
        }
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    player.move(sf::Vector2f(0, -1) * 250.f * deltaTime.asSeconds());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    player.move(sf::Vector2f(0, 1) * 250.f * deltaTime.asSeconds());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player.move(sf::Vector2f(-1, 0) * 250.f * deltaTime.asSeconds());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player.move(sf::Vector2f(1, 0) * 250.f * deltaTime.asSeconds());
                }
                break;
            case sf::Event::MouseButtonReleased:
				if (m_gameState == GAME_STATE::MAIN_MENU)
				{
					m_gameState = m_mainMenu.buttonPressed(m_window, event.mouseButton);
				    
					if (m_gameState == GAME_STATE::EXIT)
                    {
						m_window.close();
					}
                }
				break;
            default:
                break;
            }
        }

        // Define the boundaries of the view
        const float viewWidth = view.getSize().x;
        const float viewHeight = view.getSize().y;
        const float halfViewWidth = viewWidth / 2.0f;
        const float halfViewHeight = viewHeight / 2.0f;

        // Get player's position
        sf::Vector2f playerPos = player.getPosition();

        // Adjust the view center based on the player's position within boundaries
        float viewCenterX = std::max(halfViewWidth, std::min(playerPos.x, windowHeight - halfViewWidth));
        float viewCenterY = std::max(halfViewHeight, std::min(playerPos.y, WindowWidth - halfViewHeight));

        view.setCenter(viewCenterX, viewCenterY);

        m_window.clear();


        switch (m_gameState)
        {
		case::GAME_STATE::MAIN_MENU:
			m_mainMenu.drawMainMenu(m_window);
			break;
		case::GAME_STATE::NEW_GAME:
			break;
		case::GAME_STATE::EXIT:
			break;
		case::GAME_STATE::LOAD_GAME:
			break;
		case::GAME_STATE::GAME_RUNNING:
            m_window.setView(view);
            m_window.draw(background);
            m_window.draw(player);
			break;
        case::GAME_STATE::ENDGAME:
			break;
        default:
            break;
        }

        m_window.display();
    }
}


