#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
#include "GameScreenMenu.h"
#include "GameScreenGameover.h"
#include "GameScreenHighscores.h"

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

	GameScreenIntro* tempIntro;
	GameScreenMenu* tempMenu;
	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	GameScreenGameover* tempOver;
	GameScreenHighscores* tempScores;

	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
			tempIntro = new GameScreenIntro();
			mCurrentScreen = (GameScreen*)tempIntro;
			tempIntro = NULL;
		break;

		case SCREEN_MENU:
			tempMenu = new GameScreenMenu();
			mCurrentScreen = (GameScreen*)tempMenu;
			tempMenu = NULL;
		break;

		case SCREEN_LEVEL1:
			tempScreen1 = new GameScreenLevel1();
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
		break;

		case SCREEN_LEVEL2:
			tempScreen2 = new GameScreenLevel2();
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
			break;
		
		case SCREEN_GAMEOVER:
			tempOver = new GameScreenGameover();
			mCurrentScreen = (GameScreen*)tempOver;
			tempOver = NULL;
		break;
		
		case SCREEN_HIGHSCORES:
			tempScores = new GameScreenHighscores();
			mCurrentScreen = (GameScreen*)tempScores;
			tempScores = NULL;
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------