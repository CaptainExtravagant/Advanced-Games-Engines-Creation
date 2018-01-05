#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//mCola = new GameObject(Vector3D(0, 0, 0), "Can.obj");

	mCamera = new Camera();

	mCubeCore = new RubiksCubeCore();
	
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
	SetMaterial();
		
	/*
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	*/

	mCamera->Render();
	//mCola->Render();
	mCubeCore->Render();

}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	mCamera->Update(deltaTime, e);
	//mCola->Update(deltaTime, e);
	mCubeCore->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetLight()
{
	lighting light = {
		{0.2f, 0.2f, 0.2f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f},
		{0.5f, 0.5f, 0.5f, 1.0f}
	};
	//Position of the light in homogeneous coordindates (x, y, z, w)
	//w should be 0 for directional lights, 1 for spotlights
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::SetMaterial()
{
	material material = {
		{0.80f, 0.05f, 0.05f, 1.0f},
		{0.80f, 0.05f, 0.05f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}