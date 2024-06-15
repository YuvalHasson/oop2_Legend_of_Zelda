#include "BackToGameButton.h"

BackToGameButton::BackToGameButton(State* state)
{
	setText("Resume", sf::Vector2f(70, 750));
	setState(state);
}

void BackToGameButton::execute()
{
	getState()->backToGame();
}
