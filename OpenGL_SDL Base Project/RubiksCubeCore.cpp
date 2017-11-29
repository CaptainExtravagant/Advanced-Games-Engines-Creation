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

void RubiksCubeCore::SpawnBlocks()
{

	//Spawn Top Layer (1)
		//Center
			oBlockList, oTopBlocks.push_back(new RubiksCubeBlockCenter(1));
		//Edges
			//Front
				oBlockList, oTopBlocks, oFrontBlocks.push_back(new RubiksCubeBlockEdge(1, 3));
			//Back
				oBlockList, oTopBlocks, oBackBlocks.push_back(new RubiksCubeBlockEdge(1, 4));
			//Right
				oBlockList, oTopBlocks, oRightBlocks.push_back(new RubiksCubeBlockEdge(1, 5));
			//Left
				oBlockList, oTopBlocks, oLeftBlocks.push_back(new RubiksCubeBlockEdge(1, 6));
		//Corners
			//Front Right
				oBlockList, oTopBlocks, oFrontBlocks, oRightBlocks.push_back(new RubiksCubeBlockCorner(1, 3, 5));
			//Front Left
				oBlockList, oTopBlocks, oFrontBlocks, oLeftBlocks.push_back(new RubiksCubeBlockCorner(1, 3, 6));
			//Back Right
				oBlockList, oTopBlocks, oBackBlocks, oRightBlocks.push_back(new RubiksCubeBlockCorner(1, 4, 5));
			//Back Left
				oBlockList, oTopBlocks, oBackBlocks, oLeftBlocks.push_back(new RubiksCubeBlockCorner(1, 4, 6));

	//Spawn Bottom Layer (2)
		//Center
			oBlockList, oBottomBlocks.push_back(new RubiksCubeBlockCenter(2));
		//Edges
			//Front
				oBlockList, oBottomBlocks, oFrontBlocks.push_back(new RubiksCubeBlockEdge(2, 3));
			//Back
				oBlockList, oBottomBlocks, oBackBlocks.push_back(new RubiksCubeBlockEdge(2, 4));
			//Right
				oBlockList, oBottomBlocks, oRightBlocks.push_back(new RubiksCubeBlockEdge(2, 5));
			//Left
				oBlockList, oBottomBlocks, oLeftBlocks.push_back(new RubiksCubeBlockEdge(2, 6));
		//Corners
			//Front Right
				oBlockList, oBottomBlocks, oFrontBlocks, oRightBlocks.push_back(new RubiksCubeBlockCorner(2, 3, 5));
			//Front Left
				oBlockList, oBottomBlocks, oFrontBlocks, oLeftBlocks.push_back(new RubiksCubeBlockCorner(2, 3, 6));
			//Back Right
				oBlockList, oBottomBlocks, oBackBlocks, oRightBlocks.push_back(new RubiksCubeBlockCorner(2, 4, 5));
			//Back Left
				oBlockList, oBottomBlocks, oBackBlocks, oLeftBlocks.push_back(new RubiksCubeBlockCorner(2, 4, 6));

	//Spawn Front Layer (3)
		//Center
			oBlockList, oFrontBlocks.push_back(new RubiksCubeBlockCenter(3));
		//Edges
			//Right
				oBlockList, oFrontBlocks, oRightBlocks.push_back(new RubiksCubeBlockEdge(3, 5));
			//Left
				oBlockList, oFrontBlocks, oLeftBlocks.push_back(new RubiksCubeBlockEdge(3, 6));

	//Spawn Back Layer (4)
		//Center
			oBlockList, oBackBlocks.push_back(new RubiksCubeBlockCenter(4));
		//Edges
			//Right
				oBlockList, oBackBlocks, oRightBlocks.push_back(new RubiksCubeBlockEdge(4, 5));
			//Left
				oBlockList, oBackBlocks, oLeftBlocks.push_back(new RubiksCubeBlockEdge(4, 6));

	//Spawn Right Layer (5)
		//Center
			oBlockList, oRightBlocks.push_back(new RubiksCubeBlockCenter(5));

	//Spawn Left Layer (6)
		//Center
			oBlockList, oLeftBlocks.push_back(new RubiksCubeBlockCenter(6));
}