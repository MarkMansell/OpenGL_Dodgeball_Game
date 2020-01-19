#include "MainMenu.h"
#include "Constants.h"


MainMenu::MainMenu(GameScreenManager* gsm) : GameScreen(gsm)
{
	selected = MENU_NONE;
	mMenuItems.push_back("Dodge Ball");
	mMenuItems.push_back("Ball Collect");
	mMenuItems.push_back("Infomation");
	mMenuItems.push_back("Exit");

	if (mMenuItems.size() != 0)
	{
		selected = MENU_LEVEL1;
	}
	mInstructions.push_back("Use Arrows to navigate the menu");
	mInstructions.push_back("Push Enter to select");
}


MainMenu::~MainMenu()
{
}

void MainMenu::Render()
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
		if (i == selected)
		{
			//glColor3f(1.0f, 0.4f, 0.0f);
			OutputLine(38, 80 - 10 * i, "> " + mMenuItems[i] + " <");
		}
		else
		{
			//glColor3f(0.0f, 0.0f, 0.0f);
			OutputLine(40, 80 - 10 * i, mMenuItems[i]);
		}
		

	}
	for (size_t j = 0; j < mInstructions.size(); j++)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		OutputLine(30, 40 - 10 * j, mInstructions[j]);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void MainMenu::Update(float deltatime, SDL_Event e)
{
	HandleInput(e);
}

void MainMenu::HandleInput(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (selected > 0)
			{
				selected = selected - 1;
			}
			break;	

		case SDLK_DOWN:
			if (selected < mMenuItems.size() - 1)
			{
				selected++;
			}
			break;

		case SDLK_RETURN:
			HandleSelectedItem();
			break;

		}
		break;
	}
}

void MainMenu::HandleSelectedItem()
{
	if (selected == -1) // MENU_NONE
	{
	}
	else if (selected == 0) // MENU_LEVEL1
	{
		mManager->ChangeScreen(SCREEN_LEVEL1);
	}
	else if (selected == 1) // MENU_LEVEL2
	{
		mManager->ChangeScreen(SCREEN_LEVEL2);
	}
	else if (selected == 2) // MENU_EXIT
	{
		mManager->ChangeScreen(SCREEN_INFO);
	}
	else if (selected == 3)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
}