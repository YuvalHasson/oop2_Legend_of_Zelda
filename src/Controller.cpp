#include "Controller.h"
#include <iostream> //for debugging

Controller::Controller()
	: m_window(sf::VideoMode(windowHeight, WindowWidth), "Zelda", sf::Style::Close | sf::Style::Titlebar)
{
	m_window.setFramerateLimit(60);
	m_window.setIcon(Resources::getResource().getIcon()->getSize().x, Resources::getResource().getIcon()->getSize().y, Resources::getResource().getIcon()->getPixelsPtr());
    m_gameState = GAME_STATE::MAIN_MENU;
}

Controller::~Controller()
{
}

void Controller::run()
{

    sf::Sprite background;
    background.setTexture(*Resources::getResource().getTexture(TEXTURE::Map));

    sf::View view(sf::FloatRect(sf::Vector2f(80, 140), sf::Vector2f(250, 265)));

    //tmp
    sf::Text fpsText;
    fpsText.setFont(*Resources::getResource().getFont());
    fpsText.setCharacterSize(20);
	fpsText.setString("FPS     0");
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setPosition(10.f, 10.f);

    int frameCount = 0;
    float elapsedTime = 0.f;

    sf::Clock clock;
    sf::Time deltaTime;
    while (m_window.isOpen())
    {
        deltaTime = clock.restart();
        if (m_gameState == GAME_STATE::NEW_GAME)
        {
            m_board.setMap();
			m_board.makeLink();
            m_board.addStaticObject(sf::Vector2f(50.f,50.f));


            view.setCenter(m_board.getSprite(0).getPosition()); // not suppose to be here
            m_gameState = GAME_STATE::GAME_RUNNING;
        }

		if (m_gameState == GAME_STATE::GAME_RUNNING)
        {
            // Define the boundaries of the view
            const float viewWidth = view.getSize().x;
            const float viewHeight = view.getSize().y;
            const float halfViewWidth = viewWidth / 2.0f;
            const float halfViewHeight = viewHeight / 2.0f;

            // Get player's position
            sf::Vector2f playerPos = m_board.getSprite(0).getPosition();

            // Adjust the view center based on the player's position within boundaries
            float viewCenterX = std::max(halfViewWidth, std::min(playerPos.x, Resources::getResource().getTexture(TEXTURE::Map)->getSize().x - halfViewWidth));
            float viewCenterY = std::max(halfViewHeight, std::min(playerPos.y, Resources::getResource().getTexture(TEXTURE::Map)->getSize().y - halfViewHeight));

            view.setCenter(viewCenterX, viewCenterY);

			// Move the player
			m_board.move(deltaTime);
			// Handle collisions
			m_board.handleCollision();
			m_board.update(deltaTime);

            fpsText.setPosition(view.getCenter().x - viewWidth / 2 + 10.f, view.getCenter().y - viewHeight / 2 + 10.f);
		}

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
				if (m_gameState == GAME_STATE::MAIN_MENU)
				{
					m_mainMenu.buttonPressed(m_window, event.mouseButton);
					m_gameState = m_mainMenu.getGameState();
				    
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

        float deltaTime = clock.getElapsedTime().asSeconds();
        elapsedTime += deltaTime;
        frameCount++;
        if (elapsedTime >= 1.0f) {
            int fps = (int)frameCount / elapsedTime;
            fpsText.setString("FPS    " + std::to_string(fps));

            frameCount = 0;
            elapsedTime = 0.f;
        }

        m_window.clear();


        sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());

        switch (m_gameState)
        {
		case::GAME_STATE::MAIN_MENU:
			m_mainMenu.drawMainMenu(m_window);
            m_mainMenu.overButton(m_window);
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
			m_board.draw(m_window, viewBounds);
			break;
        case::GAME_STATE::ENDGAME:
			break;
        default:
            break;
        }
        m_window.draw(fpsText);

        m_window.display();
    }
}