#ifndef _GAMESCREEN_MENU_H
#define _GAMESCREEN_MENU_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>

class GameScreenMenu : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenMenu();
	~GameScreenMenu();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	//--------------------------------------------------------------------------------------------------
private:

	float mCurrentTime;
};

#endif