#include "RubiksCubeBlock.h"

#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"

RubiksCubeBlock::RubiksCubeBlock() : GameObject(Vector3D(0, 0, 0), "Block.obj")
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

		glTranslatef(mTransform.position.x, mTransform.position.y, mTransform.position.z);

		glRotatef(mTransform.rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(mTransform.rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(mTransform.rotation.x, 1.0f, 0.0f, 0.0f);

		//glRotatef(yAngle, yAxis.x, yAxis.y, yAxis.z);
		//glRotatef(zAngle, zAxis.x, zAxis.y, zAxis.z);
		//glRotatef(xAngle, xAxis.x, xAxis.y, xAxis.z);
			
		//glRotatef(mQuatRotation.w, mQuatRotation.x, mQuatRotation.y, mQuatRotation.z);
		
		glScalef(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);

		RenderModel();
		//DrawCube();

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
	/*
	//Reset rotation if less than 0
	if (mTransform.rotation.x < 0)
	{
		mTransform.rotation.x += 360;
	}

	if (mTransform.rotation.y < 0)
	{
		mTransform.rotation.y += 360;
	}

	if (mTransform.rotation.z < 0)
	{
		mTransform.rotation.z += 360;
	}

	//Reset rotation if more than 360
	if (mTransform.rotation.x > 360)
	{
		mTransform.rotation.x -= 360;
	}

	if (mTransform.rotation.y > 360)
	{
		mTransform.rotation.y -= 360;
	}

	if (mTransform.rotation.z > 360)
	{
		mTransform.rotation.z -= 360;
	}*/

	mQuatRotation.FromEuler(mTransform.rotation.x, mTransform.rotation.y, mTransform.rotation.z);

	mQuatRotation.GetAxisAngle(&xAxis, &xAngle);
	mQuatRotation.GetAxisAngle(&yAxis, &yAngle);
	mQuatRotation.GetAxisAngle(&zAxis, &zAngle);
	
}