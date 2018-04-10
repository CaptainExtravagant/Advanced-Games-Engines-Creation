#include "GameScreenLevel2Gameover.h"

GameScreenLevel2Gameover::GameScreenLevel2Gameover(GameScreenManager* manager, int score) : GameScreen(manager)
{
	finalScore = score;
	SetUpLevel();
}

GameScreenLevel2Gameover::~GameScreenLevel2Gameover()
{

}

bool GameScreenLevel2Gameover::SetUpLevel()
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
	mFinalScoreText = new Text2D("Final Score: " + to_string(finalScore), 45, 40);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Enable lighting
	glEnable(GL_LIGHTING);
	//Directional Light
	glEnable(GL_LIGHT0);

	return true;
}

void GameScreenLevel2Gameover::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMaterial();

	mCamera->Render();

	mGameoverText->PrintText();
	mFinalScoreText->PrintText();
}

void GameScreenLevel2Gameover::Update(float deltaTime, SDL_Event e)
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

void GameScreenLevel2Gameover::SetMaterial()
{
	material material = {
		{0.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}