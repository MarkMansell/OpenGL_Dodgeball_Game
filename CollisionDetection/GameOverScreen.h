#pragma once

#include "GameScreen.h"
#include "GameScreenManager.h"

class GameOverScreen : GameScreen
{
public:
	GameOverScreen(GameScreenManager* gsm, float leveltime, int hitcount);
	~GameOverScreen();
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	vector<string> mMenuItems;
};

