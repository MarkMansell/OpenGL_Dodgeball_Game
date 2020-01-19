#pragma once
#include "GameScreen.h"
#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"

class GameCompleteL2Screen :
	public GameScreen
{
public:
	GameCompleteL2Screen(GameScreenManager* gsm, float isp1winner);
	~GameCompleteL2Screen();
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	vector<string> mMenuItems;
};

