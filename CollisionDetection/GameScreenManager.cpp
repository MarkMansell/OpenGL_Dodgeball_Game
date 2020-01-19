#include "GameScreenManager.h"
#include "GameScreen.h"
#include "MainMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameOverScreen.h"
#include "GameCompleteL1Screen.h"
#include "GameCompleteL2Screen.h"
#include "InfoScreen.h"

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}


	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	MainMenu* tempMenuScreen;
	GameOverScreen* tempGameOverScreen;
	GameCompleteL1Screen* tempCompleteL1Screen;
	GameCompleteL2Screen* tempCompleteL2Screen;
	InfoScreen* tempInfoScreen;


	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
		break;

		case SCREEN_MENU:
			tempMenuScreen = new MainMenu(this);
			mCurrentScreen = (GameScreen*)tempMenuScreen;
			tempMenuScreen = NULL;
		break;

		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1(this);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
		break;
		
		case SCREEN_LEVEL2:
			tempScreen2 = new GameScreenLevel2(this);
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
		break;

		case SCREEN_GAMEOVER:
			PlaySound(TEXT("Sounds/Scream"), NULL, SND_ALIAS);
			tempGameOverScreen = new GameOverScreen(this, mLevelCompleteTime, mHitCount);
			mCurrentScreen = (GameScreen*)tempGameOverScreen;
			tempGameOverScreen = NULL;
		break;
		
		case SCREEN_HIGHSCORES:
		break;

		case SCREEN_INFO:
			tempInfoScreen = new InfoScreen(this);
			mCurrentScreen = (GameScreen*)tempInfoScreen;
			tempInfoScreen = NULL;
		break;

		case SCREEN_L1_Complete:
			tempCompleteL1Screen = new GameCompleteL1Screen(this, mLevelCompleteTime, mHitCount);
			mCurrentScreen = (GameScreen*)tempCompleteL1Screen;
			tempCompleteL1Screen = NULL;
		break;

		case SCREEN_L2_Complete:
			tempCompleteL2Screen = new GameCompleteL2Screen(this, mLevel2Winner);
			mCurrentScreen = (GameScreen*)tempCompleteL2Screen;
			tempCompleteL2Screen = NULL;
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------