#ifndef _GAMESCREEN_MENU_H
#define _GAMESCREEN_MENU_H

#include <SDL.h>
#include "GameScreen.h"
#include "Camera.h"
#include <string>
#include "Button.h"

class GameScreenMenu : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenMenu(GameScreenManager* manager);
	~GameScreenMenu();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	//--------------------------------------------------------------------------------------------------
private:

	void SetLight();
	void SetMaterial();

	void UpdateTutorialText();

	float mCurrentTime;

	Button* mLevel1Button;
	Button* mLevel2Button;
	Text2D* mTutorialText;

	string level1Text;
	string level2Text;

	int focusedButton;

	Camera* mCamera;
};

#endif