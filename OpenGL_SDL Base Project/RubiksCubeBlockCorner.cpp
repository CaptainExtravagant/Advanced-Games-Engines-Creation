#include "RubiksCubeBlockCorner.h"

RubiksCubeBlockCorner::RubiksCubeBlockCorner(int side1, int side2, int side3)
{
	activeSides.push_back(side1);
	activeSides.push_back(side2);
	activeSides.push_back(side3);
	SetRotation();
	SetPosition();
}

RubiksCubeBlockCorner::~RubiksCubeBlockCorner()
{

}

void RubiksCubeBlockCorner::AssignSides(int side1, int side2, int side3)
{
	activeSides[0] = side1;
	activeSides[1] = side2;
	activeSides[2] = side3;
}

bool RubiksCubeBlockCorner::CheckForSide(int side)
{
	for (unsigned int i = 0; i < activeSides.size(); i++)
	{
		if (activeSides[i] == side)
		{
			return true;
		}
	}
	return false;
}

void RubiksCubeBlockCorner::SetRotation()
{
	if (CheckForSide(1) && CheckForSide(3) && CheckForSide(5))
	{
		//Top Front Right
	}
	else if (CheckForSide(1) && CheckForSide(3) && CheckForSide(6))
	{
		//Top Front Left
		mTransform.rotation = Vector3D(0, 0, 90);
	}
	else if (CheckForSide(1) && CheckForSide(4) && CheckForSide(5))
	{
		//Top Back Right
		mTransform.rotation = Vector3D(0, 0, -90);
	}
	else if (CheckForSide(1) && CheckForSide(4) && CheckForSide(6))
	{
		//Top Back Left
		mTransform.rotation = Vector3D(0, 0, 180);
	}
	else if (CheckForSide(2) && CheckForSide(3) && CheckForSide(5))
	{
		//Bottom Front Right
		mTransform.rotation = Vector3D(-90, 0, 0);
	}
	else if (CheckForSide(2) && CheckForSide(3) && CheckForSide(6))
	{
		//Bottom Front Left
		mTransform.rotation = Vector3D(0, 180, 0);
	}
	else if (CheckForSide(2) && CheckForSide(4) && CheckForSide(5))
	{
		//Bottom Back Right
		mTransform.rotation = Vector3D(180, 0, 0);
	}
	else if (CheckForSide(2) && CheckForSide(4) && CheckForSide(6))
	{
		//Bottom Back Left
		mTransform.rotation = Vector3D(180, 90, 0);
	}
}

void RubiksCubeBlockCorner::SetPosition()
{
	if (CheckForSide(1))
	{
		mTransform.AddPosition(Vector3D(0, 10, 0));
	}

	if (CheckForSide(2))
	{
		mTransform.AddPosition(Vector3D(0, -10, 0));
	}

	if (CheckForSide(3))
	{
		mTransform.AddPosition(Vector3D(0, 0, 10));
	}

	if (CheckForSide(4))
	{
		mTransform.AddPosition(Vector3D(0, 0, -10));
	}

	if (CheckForSide(5))
	{
		mTransform.AddPosition(Vector3D(10, 0, 0));
	}

	if (CheckForSide(6))
	{
		mTransform.AddPosition(Vector3D(-10, 0, 0));
	}
}