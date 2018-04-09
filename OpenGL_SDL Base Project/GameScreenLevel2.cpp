#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(GameScreenManager* manager) : GameScreen(manager)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mCamera;
	mCamera = NULL;

	delete mCharacterManager;
	mCharacterManager = NULL;
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMaterial();
	SetLight();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(20.0f, 0.0f, 15.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(20.0f, 0.0f, -15.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(-20.0f, 0.0f, -15.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-20.0f, 0.0f, 15.0f);
	glEnd();

	mCharacterManager->Render();

	HUD_Timer->PrintText();
	HUD_Kills->PrintText();

	if(mCamera != NULL)
		mCamera->Render(Vector3D(0, 0, 0));
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	HUD_Timer->UpdateText("Time Survived: " + to_string((int)mCurrentTime) + "s");

	mCharacterManager->Update(deltaTime, e);

	if (mCamera != NULL)
		mCamera->Update(deltaTime, e);
}

bool GameScreenLevel2::SetUpLevel()
{
	mCamera = new Camera();
	//Disable Player Control of Camera
	mCamera->SetMovementEnabled(false);
	//Set Camera to Look Down
	mCamera->SetPitch(-95.8);
	//Set Camera Position
	mCamera->SetPosition(Vector3D(0, 30, 0));

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

														//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Enable lighting
	glEnable(GL_LIGHTING);
	//Directional Light
	glEnable(GL_LIGHT0);
	
	mCharacterManager = new CharacterManager(this);
	HUD_Timer = new Text2D("Time Survived: ", 10, 95);
	HUD_Kills = new Text2D("Kills: 0", 90, 95);

	return true;
}

void GameScreenLevel2::AddKill()
{
	totalKills++;

	HUD_Kills->UpdateText("Kills: " + to_string(totalKills));
}

void GameScreenLevel2::LostGame()
{
	mScreenManager->ChangeScreen(SCREEN_MENU);
	return;
}