#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "BallSpawner.h"

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
	
	void SetLight();
	void SetMaterial();

	void RenderHUDText();
	
	float mCurrentTime = 0;
	Camera* mCamera;

	//Player
	PlayerCharacter* mPlayer;
	//Balls
	BallSpawner* mSpawner;
	//Court Plane

	//HUD Text - Balls Hit
	Text2D* mHUDBalls;
	
	//HUD Text - Timer
	Text2D* mHUDTimer;

	int courtTextureID;

};


#endif //_GAMESCREENLEVEL1_H