#include "RubiksCubeCore.h"

RubiksCubeCore::RubiksCubeCore()
{
	SpawnBlocks();
}

RubiksCubeCore::~RubiksCubeCore()
{

}

void RubiksCubeCore::Rotate(Vector3D rotationDirection)
{
	mTransform.rotation += rotationDirection;
}

void RubiksCubeCore::Update(float deltaTime, SDL_Event e)
{
	for (unsigned int i = 0; i <= oBlockList.capacity(); i++)
	{
		oBlockList[i]->Update(deltaTime, e);
	}
}

void RubiksCubeCore::Render()
{
	for (unsigned int i = 0; i <= oBlockList.capacity(); i++)
	{
		oBlockList[i]->Render();
	}

}

void RubiksCubeCore::SpawnBlocks()
{

	//Spawn Top Layer (1)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(1));
		//Edges
			//Front
				oBlockList.push_back(new RubiksCubeBlockEdge(1, 3));
			//Back
				oBlockList.push_back(new RubiksCubeBlockEdge(1, 4));
			//Right
				oBlockList.push_back(new RubiksCubeBlockEdge(1, 5));
			//Left
				oBlockList.push_back(new RubiksCubeBlockEdge(1, 6));
		//Corners
			//Front Right
				oBlockList.push_back(new RubiksCubeBlockCorner(1, 3, 5));
			//Front Left
				oBlockList.push_back(new RubiksCubeBlockCorner(1, 3, 6));
			//Back Right
				oBlockList.push_back(new RubiksCubeBlockCorner(1, 4, 5));
			//Back Left
				oBlockList.push_back(new RubiksCubeBlockCorner(1, 4, 6));

	//Spawn Bottom Layer (2)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(2));
		//Edges
			//Front
				oBlockList.push_back(new RubiksCubeBlockEdge(2, 3));
			//Back
				oBlockList.push_back(new RubiksCubeBlockEdge(2, 4));
			//Right
				oBlockList.push_back(new RubiksCubeBlockEdge(2, 5));
			//Left
				oBlockList.push_back(new RubiksCubeBlockEdge(2, 6));
		//Corners
			//Front Right
				oBlockList.push_back(new RubiksCubeBlockCorner(2, 3, 5));
			//Front Left
				oBlockList.push_back(new RubiksCubeBlockCorner(2, 3, 6));
			//Back Right
				oBlockList.push_back(new RubiksCubeBlockCorner(2, 4, 5));
			//Back Left
				oBlockList.push_back(new RubiksCubeBlockCorner(2, 4, 6));

	//Spawn Front Layer (3)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(3));
		//Edges
			//Right
				oBlockList.push_back(new RubiksCubeBlockEdge(3, 5));
			//Left
				oBlockList.push_back(new RubiksCubeBlockEdge(3, 6));

	//Spawn Back Layer (4)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(4));
		//Edges
			//Right
				oBlockList.push_back(new RubiksCubeBlockEdge(4, 5));
			//Left
				oBlockList.push_back(new RubiksCubeBlockEdge(4, 6));

	//Spawn Right Layer (5)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(5));

	//Spawn Left Layer (6)
		//Center
			oBlockList.push_back(new RubiksCubeBlockCenter(6));


	for (unsigned int i = 0; i < oBlockList.capacity(); i++)
	{
		if (oBlockList[i]->CheckForSide(1))
		{
			oTopBlocks.push_back(oBlockList[i]);
		}
		else if (oBlockList[i]->CheckForSide(2))
		{
			oBottomBlocks.push_back(oBlockList[i]);
		}
		else if (oBlockList[i]->CheckForSide(3))
		{
			oFrontBlocks.push_back(oBlockList[i]);
		}
		else if (oBlockList[i]->CheckForSide(4))
		{
			oBackBlocks.push_back(oBlockList[i]);
		}
		else if (oBlockList[i]->CheckForSide(5))
		{
			oRightBlocks.push_back(oBlockList[i]);
		}
		else if (oBlockList[i]->CheckForSide(6))
		{
			oLeftBlocks.push_back(oBlockList[i]);
		}
	}
}