#include "RubiksCubeBlockCenter.h"

RubiksCubeBlockCenter::RubiksCubeBlockCenter(int newSide)
{
	activeSide = newSide;
	SetRotation();
	SetPosition();
}

RubiksCubeBlockCenter::~RubiksCubeBlockCenter()
{

}

void RubiksCubeBlockCenter::SetRotation()
{
	switch (activeSide)
	{
	case 1:
		mTransform.rotation = Vector3D(0, 0, 0);
		break;
	case 2:
		mTransform.rotation = Vector3D(180, 0, 0);
		break;
	case 3:
		mTransform.rotation = Vector3D(90, 0, 0);
		break;
	case 4:
		mTransform.rotation = Vector3D(-90, 0, 0);
		break;
	case 5:
		mTransform.rotation = Vector3D(0, 0, 90);
		break;
	case 6:
		mTransform.rotation = Vector3D(0, 0, -90);
		break;
	}
}

bool RubiksCubeBlockCenter::CheckForSide(int side)
{
	if (activeSide == side)
		return true;

	return false;
}

void RubiksCubeBlockCenter::SetPosition()
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