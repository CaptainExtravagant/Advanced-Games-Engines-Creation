#include "RubiksCubeBlock.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"

RubiksCubeBlock::RubiksCubeBlock()
{

}

RubiksCubeBlock::~RubiksCubeBlock()
{

}

void RubiksCubeBlock::SetRotation()
{

}

void RubiksCubeBlock::SetPosition()
{

}

void RubiksCubeBlock::Render()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCube(1.0f);
		glTranslatef(GetPosition().x, GetPosition().y, GetPosition().z);
	glEnd();
}

bool RubiksCubeBlock::CheckForSide(int side)
{
	if (activeSide == side)
		return true;

	return false;
}

void RubiksCubeBlock::Update(float deltaTime, SDL_Event e)
{

}