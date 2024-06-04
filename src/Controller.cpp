#include "Controller.h"
#include <iostream> //for debugging

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

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
	view.setCenter(m_board.getSprite(0).getPosition()); // not suppose to be here

	//start of box2d testing

    // Define the gravity vector
    b2Vec2 gravity(0.0f, 0.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    // Use dynamic allocation as this is a big object, and allocating it on the
    // stack causes compiler warning on function stack usage
    auto world = std::make_unique<b2World>(gravity);

    // Define the ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world

    //b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body
    //groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic
    fixtureDef.density = 1.0f;

    // Override the default friction
    fixtureDef.friction = 0.3f;

    // Add the shape to the body
    body->CreateFixture(&fixtureDef);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    auto worldStepCounter = 60;


    while (m_window.isOpen())
    {
        if (m_gameState == GAME_STATE::NEW_GAME)
        {
            m_gameState = GAME_STATE::GAME_RUNNING;
        }

        if (worldStepCounter--)
        {
            // First, cause the world to be updated to the next step
            world->Step(timeStep, velocityIterations, positionIterations);

            // Then, get the new position and angle from box2d object ...
            position = body->GetPosition();
            // (box2d numbers are not in pixels, so we need some scaling here)
            position *= 100.f;
            angle = body->GetAngle();

            // ... and update the SFML object with this info
            // Note: again, in real code, this data flow should be part of a
            // proper member function of the class representation the whole
            // object, not handled by main/controller or any similar class
            m_board.getSprite(0).setPosition(position.x, position.y);
            m_board.getSprite(0).setRotation(angle * 180.f / b2_pi);
        }

        //tmp key press
        if (sf::Event::KeyPressed)
        {
            b2Vec2 velocity(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                velocity.y -= 2.f;
				//m_board.getSprite(0).move(sf::Vector2f(0, -1) * 100.f * deltaTime.asSeconds());
                //player.move(sf::Vector2f(0, -1) * 25.f * deltaTime.asSeconds());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
				velocity.y += 2.f;
				//m_board.getSprite(0).move(sf::Vector2f(0, 1) * 100.f * deltaTime.asSeconds());
                //player.move(sf::Vector2f(0, 1) * 25.f * deltaTime.asSeconds());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
				velocity.x -= 2.f;
				//m_board.getSprite(0).move(sf::Vector2f(-1, 0) * 100.f * deltaTime.asSeconds());
                //player.move(sf::Vector2f(-1, 0) * 25.f * deltaTime.asSeconds());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
				velocity.x += 2.f;
				//m_board.getSprite(0).move(sf::Vector2f(1, 0) * 100.f * deltaTime.asSeconds());
                //player.move(sf::Vector2f(1, 0) * 25.f * deltaTime.asSeconds());
            }
			body->SetLinearVelocity(velocity);
        }
		//tmp key press

		//end of box2d testing

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
           // m_window.draw(player);
			break;
        case::GAME_STATE::ENDGAME:
			break;
        default:
            break;
        }

        m_window.display();
    }
}


