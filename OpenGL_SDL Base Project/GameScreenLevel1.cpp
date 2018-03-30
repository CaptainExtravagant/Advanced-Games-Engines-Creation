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

	//glEnable(GL_TEXTURE_2D);
	//
	//Texture2D* texture = new Texture2D();
	//texture->Load("BlockUV.raw", 1024, 1024);
	//
	//glBindTexture(GL_TEXTURE_2D, texture->GetID());
	//
	////Set parameters to render correctly
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
		
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(2.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 2.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 2.0f);
	//glEnd();
	

	mCamera->Render();

	RenderHUDText();
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	mCamera->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::RenderHUDText()
{
	//Text position
	float x = 5;
	float y = 95;

	//Lines of text
	string text[9];

	//Input text
	text[0] = "INSTRUCTIONS:";
	text[1] = "'Q' and 'A' move the left side";
	text[2] = "'R' and 'F' move the right side";
	text[3] = "'W' and 'E' move the top side";
	text[4] = "'S' and 'D' move the bottom side";
	text[5] = "'Z' and 'X' move the front side";
	text[6] = "'C' and 'V' move the back side";
	text[7] = "Move the mouse to look around";
	text[8] = "Use the arrow keys to move around";

	//Add text to screen
	for (int i = 0; i < 9; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		OutputLine(x, y, text[i]);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		y -= 2;
	}
}

void GameScreenLevel1::SetLight()
{
	lighting light = {
		{0.2f, 0.2f, 0.2f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f},
		{0.5f, 0.5f, 0.5f, 1.0f}
	};
	//Position of the light in homogeneous coordindates (x, y, z, w)
	//w should be 0 for directional lights, 1 for spotlights
	float light_pos[] = { 10.0f, 10.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::SetMaterial()
{
	material material = {
		{0.95f, 0.95f, 0.95f, 1.0f},
		{0.95f, 0.95f, 0.95f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

void GameScreenLevel1::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}