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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	splashTimer = 5.0f;
	mCurrentTime = 0.0f;
	//Display splash image
	mLogoText = new Text2D("Floating Point: Olly Rippon", 40, 50);

	return true;
}

void GameScreenIntro::Render()
{
	mLogoText->PrintText();
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