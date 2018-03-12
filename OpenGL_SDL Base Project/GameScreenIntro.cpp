#include "GameScreenIntro.h"

GameScreenIntro::GameScreenIntro()
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{

}

bool GameScreenIntro::SetUpLevel()
{
	splashTimer = 5.0f;
	//Display splash image
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
	}
}