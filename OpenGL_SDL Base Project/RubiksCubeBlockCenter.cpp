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

void RubiksCubeBlockCenter::SetPosition()
{
	switch (activeSide)
	{
	case 1:
		mTransform.position = Vector3D(0, 10, 0);
		break;
	case 2:
		mTransform.position = Vector3D(0, -10, 0);
		break;
	case 3:
		mTransform.position = Vector3D(0, 0, 10);
		break;
	case 4:
		mTransform.position = Vector3D(0, 0, -10);
		break;
	case 5:
		mTransform.position = Vector3D(10, 0, 0);
		break;
	case 6:
		mTransform.position = Vector3D(-10, 0, 0);
		break;
	}
}