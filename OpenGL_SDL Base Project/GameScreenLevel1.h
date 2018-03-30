#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager* manager);
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

//--------------------------------------------------------------------------------------------------
private:

	void OutputLine(float x, float y, string text);

	void RenderHUDText();
	
	float mCurrentTime;
	Camera* mCamera;

	void SetLight();
	void SetMaterial();
};


#endif //_GAMESCREENLEVEL1_H