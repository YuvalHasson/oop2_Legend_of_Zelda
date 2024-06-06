#include "Controller.h"
#include <iostream> //for debugging

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

    sf::Sprite background;
    background.setTexture(*Resources::getResource().getTexture(TEXTURE::Map));

    sf::View view(sf::FloatRect(sf::Vector2f(80, 140), sf::Vector2f(250, 265)));

	//start of box2d testing

    // Define the gravity vector
    b2Vec2 gravity(0.0f, 0.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    // Use dynamic allocation as this is a big object, and allocating it on the
    // stack causes compiler warning on function stack usage
    auto world = std::make_unique<b2World>(gravity);

 

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    auto worldStepCounter = 60;
    
    sf::Clock clock;
    sf::Time deltaTime;
    
    while (m_window.isOpen())
    {
        deltaTime = clock.restart();
        if (m_gameState == GAME_STATE::NEW_GAME)
        {
			m_board.makeLink(*world);
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
		}

        if (worldStepCounter--)
        {
            world->Step(timeStep, velocityIterations, positionIterations);
			m_board.update();
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
			m_board.draw(m_window);
			break;
        case::GAME_STATE::ENDGAME:
			break;
        default:
            break;
        }

        m_window.display();
    }
}


