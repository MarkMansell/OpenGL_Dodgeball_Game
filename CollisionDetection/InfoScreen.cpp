#include "InfoScreen.h"


InfoScreen::InfoScreen(GameScreenManager* gsm) : GameScreen(gsm)
{
	mMenuItems.push_back("Info");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Level 1: ");
	mMenuItems.push_back("Use the Arrow Keys to Move the character ");
	mMenuItems.push_back("Avoid the balls ");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Level 2: ");
	mMenuItems.push_back("Grab the doughnuts faster than the AI");
	mMenuItems.push_back("If you grab them too quickly the AI will attack");
	mMenuItems.push_back("If he catches you he will take a point off you");
	mMenuItems.push_back("If he hits you...");
	mMenuItems.push_back(" ");
	mMenuItems.push_back("Push ESCAPE to go Back");
}


InfoScreen::~InfoScreen()
{
}

void InfoScreen::Render()
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
		OutputLine(25, 80 - 5 * i, mMenuItems[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void InfoScreen::Update(float deltaTime, SDL_Event e)
{
	HandleInput(e);
}

void InfoScreen::HandleInput(SDL_Event e)
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