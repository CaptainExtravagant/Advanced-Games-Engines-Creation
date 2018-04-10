#ifndef _GAMESCREEN_LEVEL2_H
#define _GAMESCREEN_LEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "CharacterManager.h"

class GameScreenLevel2 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel2(GameScreenManager* manager);
	~GameScreenLevel2();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void AddKill();
	void LostGame();

	//--------------------------------------------------------------------------------------------------
private:
	Camera* mCamera;

	Text2D* HUD_Timer;
	Text2D* HUD_Kills;

	void SetLight();
	void SetMaterial();

	int totalKills = 0;

	bool lostGame = false;

	float mCurrentTime = 0;

	CharacterManager* mCharacterManager;

	int groundTextureID;
};

#endif