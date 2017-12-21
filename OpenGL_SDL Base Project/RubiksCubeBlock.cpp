#include "RubiksCubeBlock.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"

RubiksCubeBlock::RubiksCubeBlock() : GameObject(Vector3D(0, 0, 0), "")
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
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCube(2.0f);
		glTranslatef(mTransform.position.x, mTransform.position.y, mTransform.position.z);
		DrawCube();
	glPopMatrix();
}

void RubiksCubeBlock::DrawCube()
{
	glBegin(GL_POLYGON);
	glutSolidCube(2.0f);
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