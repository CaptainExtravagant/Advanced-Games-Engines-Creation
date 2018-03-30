#include "GameScreenIntro.h"

GameScreenIntro::GameScreenIntro(GameScreenManager* manager) : GameScreen(manager)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{

}

bool GameScreenIntro::SetUpLevel()
{
	splashTimer = 5.0f;
	mCurrentTime = 0.0f;
	//Display splash image

	return true;
}

void GameScreenIntro::Render()
{

}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	if (mCurrentTime >= splashTimer)
	{
		//Change to Main Menu
		mScreenManager->ChangeScreen(SCREEN_MENU);
	}
}