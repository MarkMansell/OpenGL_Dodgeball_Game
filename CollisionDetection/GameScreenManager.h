#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
	void SetLevelInfo(float leveltime, int hitcount) { mLevelCompleteTime = leveltime; mHitCount = hitcount; }
	void SetLevel2Winner(bool isplayerwinner) { mLevel2Winner = isplayerwinner; }

private:
	GameScreen* mCurrentScreen;
	float mLevelCompleteTime;
	bool mLevel2Winner;
	int mHitCount;
};


#endif //_GAMESCREENMANAGER_H