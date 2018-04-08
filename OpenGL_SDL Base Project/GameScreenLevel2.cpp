#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(GameScreenManager* manager) : GameScreen(manager)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mCamera;
	mCamera = NULL;
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

	mCamera->Render(Vector3D(0, 0, 0));
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	mCharacterManager->Update(deltaTime, e);

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
	
	mCharacterManager = new CharacterManager();

	return true;
}