#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

	void SetLevel2Score(int score) { level2Score = score; }

private:
	GameScreen* mCurrentScreen;

	int level2Score;

};


#endif //_GAMESCREENMANAGER_H