#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "BallSpawner.h"
#include "SoundEffect.h"

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
	bool winScreen = false;
	float winTimer = 5.0f;
	float finalScore;

	void OpenWinScreen();
	
	void SetLight();
	void SetMaterial();

	void RenderHUDText();

	void AddBallToPlayer();
	
	float mCurrentTime = 0;
	Camera* mCamera;

	SoundEffect* mScreamSound;
	SoundEffect* mRewardSound;

	//Player
	PlayerCharacter* mPlayer;
	//Balls
	BallSpawner* mSpawner;

	//HUD Text - Balls Hit
	Text2D* mHUDBalls;
	
	//HUD Text - Timer
	Text2D* mHUDTimer;

	//HUD Text - Win Screen
	Text2D* mHUDWin;

	int courtTextureID;

};


#endif //_GAMESCREENLEVEL1_H