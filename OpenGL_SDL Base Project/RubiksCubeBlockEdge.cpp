#include "RubiksCubeBlockEdge.h"

RubiksCubeBlockEdge::RubiksCubeBlockEdge(int side1, int side2)
{
	activeSides.push_back(side1), (side2);
	SetRotation();
	SetPosition();
}

RubiksCubeBlockEdge::~RubiksCubeBlockEdge()
{

}

void RubiksCubeBlockEdge::AssignSides(int side1, int side2)
{
	activeSides[0] = side1;
	activeSides[1] = side2;
}

bool RubiksCubeBlockEdge::CheckForSide(int sideSelection)
{
	for (int i = 0; i < activeSides.capacity; i++)
	{
		if (activeSides[i] == sideSelection)
		{
			return true;
		}
	}
	return false;
}

void RubiksCubeBlockEdge::SetRotation()
{
	if (CheckForSide(1) && CheckForSide(3))
	{
		//Top Front
	}
	else if (CheckForSide(1) && CheckForSide(4))
	{
		//Top Back
		mTransform.rotation = Vector3D(-90, 0, 0);
	}
	else if (CheckForSide(1) && CheckForSide(5))
	{
		//Top Right
		mTransform.rotation = Vector3D(0, 0, 90);
	}
	else if (CheckForSide(1) && CheckForSide(6))
	{
		//Top Left
		mTransform.rotation = Vector3D(0, 0, -90);
	}
	else if (CheckForSide(2) && CheckForSide(3))
	{
		//Bottom Front
		mTransform.rotation = Vector3D(90, 0, 0);
	}
	else if (CheckForSide(2) && CheckForSide(4))
	{
		//Bottom Back
		mTransform.rotation = Vector3D(180, 0, 0);
	}
	else if (CheckForSide(2) && CheckForSide(5))
	{
		//Bottom Right
		mTransform.rotation = Vector3D(90, 0, -90);
	}
	else if (CheckForSide(2) & CheckForSide(6))
	{
		//Bottom Left
		mTransform.rotation = Vector3D(90, 0, 90);
	}
	else if (CheckForSide(3) && CheckForSide(5))
	{
		//Front Right
		mTransform.rotation = Vector3D(0, -90, 0);
	}
	else if (CheckForSide(3) && CheckForSide(6))
	{
		//Front Left
		mTransform.rotation = Vector3D(0, 90, 0);
	}
	else if (CheckForSide(4) && CheckForSide(5))
	{
		//Back Right
		mTransform.rotation = Vector3D(0, 180, -90);
	}
	else if (CheckForSide(4) && CheckForSide(6))
	{
		//Back Left
		mTransform.rotation = Vector3D(0, 180, 90);
	}
}

void RubiksCubeBlockEdge::SetPosition()
{
	if (CheckForSide(1) && CheckForSide(3))
	{
		//Top Front
		mTransform.position = Vector3D(0, 10, -10);
	}
	else if (CheckForSide(1) && CheckForSide(4))
	{
		//Top Back
		mTransform.position = Vector3D(0, 10, 10);
	}
	else if (CheckForSide(1) && CheckForSide(5))
	{
		//Top Right
		mTransform.position = Vector3D(10, 10, 0);
	}
	else if (CheckForSide(1) && CheckForSide(6))
	{
		//Top Left
		mTransform.position = Vector3D(-10, 10, 0);
	}
	else if (CheckForSide(2) && CheckForSide(3))
	{
		//Bottom Front
		mTransform.position = Vector3D(0, -10, -10);
	}
	else if (CheckForSide(2) && CheckForSide(4))
	{
		//Bottom Back
		mTransform.position = Vector3D(0, -10, 10);
	}
	else if (CheckForSide(2) && CheckForSide(5))
	{
		//Bottom Right
		mTransform.position = Vector3D(10, -10, 0);
	}
	else if (CheckForSide(2) & CheckForSide(6))
	{
		//Bottom Left
		mTransform.position = Vector3D(-10, -10, 0);
	}
	else if (CheckForSide(3) && CheckForSide(5))
	{
		//Front Right
		mTransform.position = Vector3D(10, 0, -10);
	}
	else if (CheckForSide(3) && CheckForSide(6))
	{
		//Front Left
		mTransform.position = Vector3D(-10, 0, -10);
	}
	else if (CheckForSide(4) && CheckForSide(5))
	{
		//Back Right
		mTransform.position = Vector3D(10, 0, 10);
	}
	else if (CheckForSide(4) && CheckForSide(6))
	{
		//Back Left
		mTransform.position = Vector3D(-10, 0, 10);
	}
}