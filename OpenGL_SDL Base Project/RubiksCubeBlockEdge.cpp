#include "RubiksCubeBlockEdge.h"

RubiksCubeBlockEdge::RubiksCubeBlockEdge(int side1, int side2)
{
	activeSides.push_back(side1);
	activeSides.push_back(side2);
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
	for (unsigned int i = 0; i < activeSides.size(); i++)
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