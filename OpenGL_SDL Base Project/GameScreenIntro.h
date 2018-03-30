#ifndef _GAMESCREEN_INTRO_H
#define _GAMESCREEN_INTRO_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "Text2D.h"

class GameScreenIntro : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenIntro(GameScreenManager* manager);
	~GameScreenIntro();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	//--------------------------------------------------------------------------------------------------
private:
		
	float mCurrentTime;
	float splashTimer;

	Text2D* mLogoText;
};

#endif