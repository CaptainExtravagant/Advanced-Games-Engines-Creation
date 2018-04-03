#include "GameScreenGameover.h"

GameScreenGameover::GameScreenGameover(GameScreenManager* manager) : GameScreen(manager)
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	mGameoverText = new Text2D("GAMEOVER", 45, 50);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Enable lighting
	glEnable(GL_LIGHTING);
	//Directional Light
	glEnable(GL_LIGHT0);
}

GameScreenGameover::~GameScreenGameover()
{
	//delete mGameoverText;
	//mGameoverText = NULL;
}

void GameScreenGameover::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMaterial();
	//SetLight();

	mCamera->Render();

	mGameoverText->PrintText();

}

void GameScreenGameover::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	timer -= deltaTime;

	if (timer <= 0)
	{
		mScreenManager->ChangeScreen(SCREEN_MENU);
		return;
	}

	mCamera->Update(deltaTime, e);
}
void GameScreenGameover::SetLight()
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

void GameScreenGameover::SetMaterial()
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