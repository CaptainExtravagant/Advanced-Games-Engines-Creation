#ifndef _GAMESCREEN_GAMEOVER_H
#define _GAMESCREEN_GAMEOVER_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>

class GameScreenGameover : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenGameover(GameScreenManager* manager);
	~GameScreenGameover();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	//--------------------------------------------------------------------------------------------------
private:

	float mCurrentTime;
};

#endif