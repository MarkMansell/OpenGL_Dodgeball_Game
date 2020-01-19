#include "GameCompleteL1Screen.h"
#include <Windows.h>

GameCompleteL1Screen::GameCompleteL1Screen(GameScreenManager* gsm, float gameleveltime, int hitcount) : GameScreen(gsm)
{
	mMenuItems.push_back("Level Complete");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Level Time: " + to_string(gameleveltime));
	mMenuItems.push_back("Ball Hit Count: " + to_string(hitcount));
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Push Escape to Back");

}


GameCompleteL1Screen::~GameCompleteL1Screen()
{
}

void GameCompleteL1Screen::Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100); // Clear Screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	size_t i;

	for (i = 0; i < mMenuItems.size(); i++)
	{
		OutputLine(30, 80 - 10 * i, mMenuItems[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameCompleteL1Screen::Update(float delta, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			mManager->ChangeScreen(SCREEN_MENU);
			break;
		}
	}
}