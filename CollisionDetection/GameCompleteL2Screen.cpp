#include "GameCompleteL2Screen.h"


GameCompleteL2Screen::GameCompleteL2Screen(GameScreenManager* gsm, float isp1winner) : GameScreen(gsm)
{
	mMenuItems.push_back("Level 2 Complete");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Winner: ");
	if (isp1winner == true)
	{
		mMenuItems.push_back("Player 1!");
	}
	else
	{
		mMenuItems.push_back("AI Player!");
	}

}


GameCompleteL2Screen::~GameCompleteL2Screen()
{
}

void GameCompleteL2Screen::Render()
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

void GameCompleteL2Screen::Update(float delta, SDL_Event e)
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
