#pragma once

class NewGameState
{
	public:
	virtual ~NewGameState() = default;

	virtual void update();
	virtual void render();
};
