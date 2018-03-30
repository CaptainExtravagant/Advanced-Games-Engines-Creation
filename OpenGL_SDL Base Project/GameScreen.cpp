#include "GameScreen.h"


//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen(GameScreenManager* manager)
{
	mScreenManager = manager;
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::SetLight()
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

void GameScreen::SetMaterial()
{
	material material = {
		{ 0.95f, 0.95f, 0.95f, 1.0f },
		{ 0.95f, 0.95f, 0.95f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}