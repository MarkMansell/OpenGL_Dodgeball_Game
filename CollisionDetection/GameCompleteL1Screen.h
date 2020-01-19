#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"

class GameCompleteL1Screen :
	public GameScreen
{
public:
	GameCompleteL1Screen(GameScreenManager* gsm, float gameleveltime, int hitcount);
	~GameCompleteL1Screen();
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	vector<string> mMenuItems;
};

