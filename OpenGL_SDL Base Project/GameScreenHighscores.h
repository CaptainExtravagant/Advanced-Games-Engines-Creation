#ifndef _GAMESCREEN_HIGHSCORES_H
#define _GAMESCREEN_HIGHSCORES_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>

class GameScreenHighscores : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenHighscores(GameScreenManager* manager);
	~GameScreenHighscores();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	//--------------------------------------------------------------------------------------------------
private:

	float mCurrentTime;
};

#endif