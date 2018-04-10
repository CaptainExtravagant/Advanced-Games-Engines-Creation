#ifndef _GAMESCREEN_LEVEL2_GAMEOVER_H
#define _GAMESCREEN_LEVEL2_GAMEOVER_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "Text2D.h"

class GameScreenLevel2Gameover : GameScreen
{
public:
	GameScreenLevel2Gameover(GameScreenManager* manager, int score);
	~GameScreenLevel2Gameover();

	bool SetUpLevel();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Text2D* mGameoverText;
	Text2D* mFinalScoreText;
	Camera* mCamera;

	void SetMaterial();

	int finalScore = 0;

	float timer = 5.0f;
	float mCurrentTime = 0;
};

#endif