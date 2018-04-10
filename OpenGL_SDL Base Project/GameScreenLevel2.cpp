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

	glBindTexture(GL_TEXTURE_2D, groundTextureID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(20.0f, 0.0f, 15.0f);
	glTexCoord2f(0.0f, 2.0f);
	glVertex3f(20.0f, 0.0f, -15.0f);
	glTexCoord2f(2.0f, 2.0f);
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
	if (lostGame)
	{
		mScreenManager->SetLevel2Score((int)mCurrentTime);
		mScreenManager->ChangeScreen(SCREEN_LEVEL2_GAMEOVER);
		return;
	}

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
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glEnable(GL_TEXTURE_2D);

	Texture2D* texture = new Texture2D();
	texture->Load("Ground.raw", 512, 512);

	groundTextureID = texture->GetID();

	glBindTexture(GL_TEXTURE_2D, groundTextureID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
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
	lostGame = true;
}

void GameScreenLevel2::SetMaterial()
{
	material material = {
		{ 0.10f, 0.10f, 0.10f, 1.0f },
		{ 0.80f, 0.80f, 0.80f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

void GameScreenLevel2::SetLight()
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

	lighting spotRed = {
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f }
	};
	float red_pos[] = { 10.0f, 5.0f, 8.0f, 1.0f };

	lighting spotGreen = {
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f }
	};
	float green_pos[] = { 0.0f, 5.0f, 8.0f, 1.0f };

	lighting spotBlue = {
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};
	float blue_pos[] = { -10.0f, 5.0f, 8.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, spotRed.ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotRed.diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotRed.specular);
	glLightfv(GL_LIGHT1, GL_POSITION, red_pos);

	glLightfv(GL_LIGHT2, GL_AMBIENT, spotGreen.ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, spotGreen.diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spotGreen.specular);
	glLightfv(GL_LIGHT2, GL_POSITION, green_pos);

	glLightfv(GL_LIGHT3, GL_AMBIENT, spotBlue.ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, spotBlue.diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, spotBlue.specular);
	glLightfv(GL_LIGHT3, GL_POSITION, blue_pos);
}