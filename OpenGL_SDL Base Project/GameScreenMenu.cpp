#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(GameScreenManager* manager) : GameScreen(manager)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{

}

bool GameScreenMenu::SetUpLevel()
{
	
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCamera = new Camera();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	level1Text = "Use WASD to move around. Avoid the falling balls. Reach the other side. 4 hits and you're out.";
	level2Text = "Use a gamepad to survive against waves of enemies with a friend. Left stick to move, right stick to aim and fire.";

	mTutorialText = new Text2D(level1Text, 10, 40);
	mLevel1Button = new Button(Vector2D(45, 60), "Start Level 1");
	mLevel2Button = new Button(Vector2D(45, 55), "Start Level 2");

	mLevel1Button->SetNeighborButton(mLevel2Button, 1);
	mLevel1Button->SetNeighborButton(mLevel2Button, 0);

	mLevel2Button->SetNeighborButton(mLevel1Button, 0);
	mLevel2Button->SetNeighborButton(mLevel1Button, 1);
	
	focusedButton = 0;
	mLevel2Button->ChangeFocused(0);


	return true;
}

void GameScreenMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMaterial();
	//SetLight();

	mCamera->Render();

	mLevel1Button->Render();
	mLevel2Button->Render();
	mTutorialText->PrintText();
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;


	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			switch (focusedButton)
			{
			case 0:
				mScreenManager->ChangeScreen(SCREEN_LEVEL1);
				break;
			case 1:
				mScreenManager->ChangeScreen(SCREEN_LEVEL2);
				break;
			}
			break;

		case SDLK_UP:
			switch (focusedButton)
			{
			case 0:
				mLevel1Button->ChangeFocused(0);
				focusedButton = 1;
				UpdateTutorialText();
				break;
			case 1:
				mLevel2Button->ChangeFocused(0);
				focusedButton = 0;
				UpdateTutorialText();
				break;
			}
			break;

		case SDLK_DOWN:
			switch (focusedButton)
			{
			case 0:
				mLevel1Button->ChangeFocused(1);
				focusedButton = 1;
				UpdateTutorialText();
				break;
			case 1:
				mLevel2Button->ChangeFocused(1);
				focusedButton = 0;
				UpdateTutorialText();
				break;
			}
			break;
		}
	}
}

void GameScreenMenu::UpdateTutorialText()
{
	switch (focusedButton)
	{
	case 0:
		mTutorialText->UpdateText(level1Text);
		break;

	case 1:
		mTutorialText->UpdateText(level2Text);
		break;
	}
}

void GameScreenMenu::SetLight()
{
	lighting light = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	//Position of the light in homogeneous coordindates (x, y, z, w)
	//w should be 0 for directional lights, 1 for spotlights
	float light_pos[] = { 10.0f, 10.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenMenu::SetMaterial()
{
	material material = {
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}