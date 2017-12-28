#include "RubiksCubeCore.h"

RubiksCubeCore::RubiksCubeCore() : GameObject(Vector3D(0, 0, 0), "")
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
	for (unsigned int i = 0; i < oBlockList.size(); i++)
	{
		oBlockList[i]->Update(deltaTime, e);
	}

	GameObject centerBlock();

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			break;

		case SDLK_a:
			break;

		case SDLK_w:
			break;

		case SDLK_e:
			break;

		case SDLK_s:
			break;

		case SDLK_d:
			break;

		case SDLK_r:
			break;

		case SDLK_f:
			break;
		}
	}
}

void RubiksCubeCore::Render()
{
	for (unsigned int i = 0; i < oBlockList.size(); i++)
	{
		oBlockList[i]->Render();
	}

}

void RubiksCubeCore::SpawnBlocks()
{
	//Spawn Top Layer (1)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(1));
		//Edges
			//Front
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(1, 3));
			//Back
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(1, 4));
			//Right
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(1, 5));
			//Left
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(1, 6));
		//Corners
			//Front Right
				oCornerBlocks.push_back(new RubiksCubeBlockCorner(1, 3, 5));
			//Front Left
				oCornerBlocks.push_back(new RubiksCubeBlockCorner(1, 3, 6));
			//Back Right
				oCornerBlocks.push_back(new RubiksCubeBlockCorner(1, 4, 5));
			//Back Left
				oCornerBlocks.push_back(new RubiksCubeBlockCorner(1, 4, 6));

	//Spawn Bottom Layer (2)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(2));
		//Edges
			//Front
			oEdgeBlocks.push_back(new RubiksCubeBlockEdge(2, 3));
			//Back
			oEdgeBlocks.push_back(new RubiksCubeBlockEdge(2, 4));
			//Right
			oEdgeBlocks.push_back(new RubiksCubeBlockEdge(2, 5));
			//Left
			oEdgeBlocks.push_back(new RubiksCubeBlockEdge(2, 6));
		//Corners
			//Front Right
			oCornerBlocks.push_back(new RubiksCubeBlockCorner(2, 3, 5));
			//Front Left
			oCornerBlocks.push_back(new RubiksCubeBlockCorner(2, 3, 6));
			//Back Right
			oCornerBlocks.push_back(new RubiksCubeBlockCorner(2, 4, 5));
			//Back Left
			oCornerBlocks.push_back(new RubiksCubeBlockCorner(2, 4, 6));

	//Spawn Front Layer (3)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(3));
		//Edges
			//Right
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(3, 5));
			//Left
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(3, 6));

	//Spawn Back Layer (4)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(4));
		//Edges
			//Right
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(4, 5));
			//Left
				oEdgeBlocks.push_back(new RubiksCubeBlockEdge(4, 6));

	//Spawn Right Layer (5)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(5));

	//Spawn Left Layer (6)
		//Center
			oCenterBlocks.push_back(new RubiksCubeBlockCenter(6));

	for (unsigned int i = 0; i < oCornerBlocks.size(); i++)
	{
		if (oCornerBlocks[i]->CheckForSide(1))
		{
			oTopBlocks.push_back(oCornerBlocks[i]);
		}

		if (oCornerBlocks[i]->CheckForSide(2))
		{
			oBottomBlocks.push_back(oCornerBlocks[i]);
		}

		if (oCornerBlocks[i]->CheckForSide(3))
		{
			oFrontBlocks.push_back(oCornerBlocks[i]);
		}

		if (oCornerBlocks[i]->CheckForSide(4))
		{
			oBackBlocks.push_back(oCornerBlocks[i]);
		}

		if (oCornerBlocks[i]->CheckForSide(5))
		{
			oRightBlocks.push_back(oCornerBlocks[i]);
		}

		if (oCornerBlocks[i]->CheckForSide(6))
		{
			oLeftBlocks.push_back(oCornerBlocks[i]);
		}
	}

	for (unsigned int i = 0; i < oEdgeBlocks.size(); i++)
	{
		if (oEdgeBlocks[i]->CheckForSide(1))
		{
			oTopBlocks.push_back(oEdgeBlocks[i]);
		}

		if (oEdgeBlocks[i]->CheckForSide(2))
		{
			oBottomBlocks.push_back(oEdgeBlocks[i]);
		}

		if (oEdgeBlocks[i]->CheckForSide(3))
		{
			oFrontBlocks.push_back(oEdgeBlocks[i]);
		}

		if (oEdgeBlocks[i]->CheckForSide(4))
		{
			oBackBlocks.push_back(oEdgeBlocks[i]);
		}

		if (oEdgeBlocks[i]->CheckForSide(5))
		{
			oRightBlocks.push_back(oEdgeBlocks[i]);
		}

		if (oEdgeBlocks[i]->CheckForSide(6))
		{
			oLeftBlocks.push_back(oEdgeBlocks[i]);
		}
	}

	for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
	{
		if (oCenterBlocks[i]->CheckForSide(1))
		{
			oTopBlocks.push_back(oCenterBlocks[i]);
		}

		if (oCenterBlocks[i]->CheckForSide(2))
		{
			oBottomBlocks.push_back(oCenterBlocks[i]);
		}

		if (oCenterBlocks[i]->CheckForSide(3))
		{
			oFrontBlocks.push_back(oCenterBlocks[i]);
		}

		if (oCenterBlocks[i]->CheckForSide(4))
		{
			oBackBlocks.push_back(oCenterBlocks[i]);
		}

		if (oCenterBlocks[i]->CheckForSide(5))
		{
			oRightBlocks.push_back(oCenterBlocks[i]);
		}

		if (oCenterBlocks[i]->CheckForSide(6))
		{
			oLeftBlocks.push_back(oCenterBlocks[i]);
		}
	}

	for (unsigned int i = 0; i < oCornerBlocks.size(); i++)
	{
		oBlockList.push_back(oCornerBlocks[i]);
	}

	for (unsigned int i = 0; i < oEdgeBlocks.size(); i++)
	{
		oBlockList.push_back(oEdgeBlocks[i]);
	}

	for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
	{
		oBlockList.push_back(oCenterBlocks[i]);
	}

}