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
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	
	Texture2D* texture = new Texture2D();
	texture->Load("Court.raw", 512, 512);
	
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	
	//Set parameters to render correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	mHUDTimer = new Text2D("Timer: ", 5, 95);
	mHUDBalls = new Text2D("Balls Hit: 0", 5, 90);
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetLight();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(12.0f, 0.0f, 8.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(12.0f, 0.0f, -8.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(-12.0f, 0.0f, -8.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-12.0f, 0.0f, 8.0f);
	glEnd();

	mCamera->Render();

	RenderHUDText();
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	mHUDTimer->UpdateText("Timer: " + to_string((int)mCurrentTime));

	mCamera->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::RenderHUDText()
{
	mHUDTimer->PrintText();
	mHUDBalls->PrintText();
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

	
}