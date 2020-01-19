#include "GameScreen.h"


//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen(GameScreenManager* gsm)
{
	mManager = gsm;
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::OutputLine(float x, float y, string text)
{

	glRasterPos2d(x, y); //Location of text on screen

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}