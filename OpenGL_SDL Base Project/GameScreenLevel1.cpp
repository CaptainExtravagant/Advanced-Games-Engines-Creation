#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture2D.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1(GameScreenManager* manager) : GameScreen(manager)
{
	mScreamSound = new SoundEffect();
	mScreamSound->LoadClip("Scream.wav");

	mRewardSound = new SoundEffect();
	mRewardSound->LoadClip("Win.wav");

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	mCamera = new Camera();
	mCamera->SetMovementEnabled(true);

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Enable lighting
	glEnable(GL_LIGHTING);
	//Directional Light
	glEnable(GL_LIGHT0);

	//Spotlights
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glEnable(GL_TEXTURE_2D);

	mPlayer = new PlayerCharacter(Vector3D(-14, 2, 0), "Ball.obj", "GreenBall.raw");

	mSpawner = new BallSpawner();
		
	Texture2D* texture = new Texture2D();
	texture->Load("Court.raw", 512, 512);
	
	courtTextureID = texture->GetID();

	glBindTexture(GL_TEXTURE_2D, courtTextureID);
	
	//Set parameters to render correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	mHUDTimer = new Text2D("Timer: ", 5, 95);
	mHUDBalls = new Text2D("Balls Hit: 0", 5, 90);
	mHUDWin = new Text2D("", 50, 90);
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
	delete mCamera;
	mCamera = NULL;

	delete mScreamSound;
	mScreamSound = NULL;

	delete mRewardSound;
	mRewardSound = NULL;

	delete mSpawner;
	mSpawner = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMaterial();
	SetLight();

	mPlayer->Render();
	mSpawner->Render();
	
	//Draw Court
	glBindTexture(GL_TEXTURE_2D, courtTextureID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(12.0f, 0.0f, 8.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(12.0f, 0.0f, -8.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(-16.0f, 0.0f, -8.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-16.0f, 0.0f, 8.0f);
	glEnd();

	mCamera->Render(mPlayer);

	RenderHUDText();
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	if (!winScreen)
	{
		mPlayer->Update(deltaTime, e);

		if (mPlayer->GetPosition().x >= 12)
		{
			//Play Sound
			mRewardSound->Play();

			//Win Game (Highscore Level)
			finalScore = mCurrentTime;
			OpenWinScreen();
		}

		mSpawner->Update(deltaTime, e);

		if (mSpawner->CheckPlayerCollision(mPlayer))
		{
			mPlayer->HitBall();
			mHUDBalls->UpdateText("Balls Hit: " + to_string(mPlayer->GetHits()));
			AddBallToPlayer();

			if (mPlayer->GetHits() >= 4)
			{
				//Play Sound
				mScreamSound->Play();

				//Change Level (GameOver)
				mScreenManager->ChangeScreen(SCREEN_GAMEOVER);
				return;

			}
		}

		mHUDTimer->UpdateText("Timer: " + to_string((int)mCurrentTime));
	}
	else
	{
		winTimer -= deltaTime;
		if (winTimer <= 0)
		{
			mScreenManager->ChangeScreen(SCREEN_MENU);
			return;
		}
	}

	mCamera->Update(deltaTime, e);
}

void GameScreenLevel1::OpenWinScreen()
{
	winScreen = true;
	mHUDWin->UpdateText("Final Score: " + to_string(finalScore));

}

void GameScreenLevel1::AddBallToPlayer()
{
	GameObject* newBall = new GameObject(Vector3D(0, 0, 0), "Ball.obj", "OrangeBall.raw");

	newBall->SetScale(Vector3D(0.5, 0.5, 0.5));

	mPlayer->AddChild(newBall);

	newBall->SetPosition(Vector3D(-4 * mPlayer->GetHits(), 0, 0));
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::RenderHUDText()
{
	mHUDTimer->PrintText();
	mHUDBalls->PrintText();
	mHUDWin->PrintText();
}

void GameScreenLevel1::SetMaterial()
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

void GameScreenLevel1::SetLight()
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
		{1.0f, 0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 0.0f, 1.0f}
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