#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
#include "GameScreenManager.h"
#include <time.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Text2D.h"

using namespace std;

class GameScreen
{
public:
	GameScreen(GameScreenManager* manager);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:
	GameScreenManager* mScreenManager;

	virtual void SetMaterial();
	virtual void SetLight();
};


#endif //_GAMESCREEN_H