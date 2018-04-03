#ifndef _GAMESCREEN_GAMEOVER_H
#define _GAMESCREEN_GAMEOVER_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "Text2D.h"

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
	Text2D* mGameoverText;
	Camera* mCamera;

	void SetLight();
	void SetMaterial();

	float timer = 5.0f;

	float mCurrentTime = 0;
};

#endif