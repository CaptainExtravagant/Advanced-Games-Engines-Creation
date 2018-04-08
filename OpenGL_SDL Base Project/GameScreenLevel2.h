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

	//--------------------------------------------------------------------------------------------------
private:
	Camera* mCamera;

	float mCurrentTime = 0;

	CharacterManager* mCharacterManager;
};

#endif