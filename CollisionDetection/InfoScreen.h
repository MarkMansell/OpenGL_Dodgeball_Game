#pragma once
#include "GameScreenManager.h"
#include "GameScreen.h"

class InfoScreen :
	public GameScreen
{
public:
	InfoScreen(GameScreenManager* gsm);
	~InfoScreen();
	void Render();
	void Update(float deltaTime, SDL_Event e);

protected:
	void HandleInput(SDL_Event e);

private:
	vector<string> mMenuItems;
};

