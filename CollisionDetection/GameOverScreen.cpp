#include "GameOverScreen.h"


GameOverScreen::GameOverScreen(GameScreenManager* gsm, float leveltime, int hitcount) : GameScreen(gsm)
{
	mMenuItems.push_back("Game Over");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Level Time: " + to_string(leveltime));
	mMenuItems.push_back("Ball Hit Count: " + to_string(hitcount));
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Push ESCAPE to go Back");
}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::Render()
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
		OutputLine(40, 80 - 10 * i, mMenuItems[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameOverScreen::Update(float delta, SDL_Event e)
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