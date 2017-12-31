#include "RubiksCubeCore.h"
#include <iostream>

RubiksCubeCore::RubiksCubeCore() : GameObject(Vector3D(0, 0, 0), "")
{
	SpawnBlocks();
	rotating = false;
	activeCenter = NULL;
}

RubiksCubeCore::~RubiksCubeCore()
{
	activeCenter = NULL;
	delete activeCenter;
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

	if (!rotating)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_q:
				rotatingSide = 6;
				positive = false;
				rotating = true;
				break;

			case SDLK_a:
				rotatingSide = 6;
				positive = true;
				rotating = true;
				break;

			case SDLK_w:
				rotatingSide = 1;
				positive = false;
				rotating = true;
				break;

			case SDLK_e:
				rotatingSide = 1;
				positive = true;
				rotating = true;
				break;

			case SDLK_s:
				rotatingSide = 2;
				positive = false;
				rotating = true;
				break;

			case SDLK_d:
				rotatingSide = 2;
				positive = true
					;
				rotating = true;
				break;

			case SDLK_r:
				rotatingSide = 5;
				positive = false;
				rotating = true;
				break;

			case SDLK_f:
				rotatingSide = 5;
				positive = true;
				rotating = true;
				break;

			case SDLK_z:
				rotatingSide = 3;
				positive = true;
				rotating = true;
				break;

			case SDLK_x:
				rotatingSide = 3;
				positive = false;
				rotating = true;
				break;

			case SDLK_c:
				rotatingSide = 4;
				positive = true;
				rotating = true;
				break;

			case SDLK_v:
				rotatingSide = 4;
				positive = false;
				rotating = true;
				break;
			}
		}
	}
	
	if(rotating)
	{
		RotateSide();
		
		if (activeCenter != NULL)
		{
			/*
			if (activeCenter->GetRotation().x == 0 || activeCenter->GetRotation().x == 90 || activeCenter->GetRotation().x == 180 || activeCenter->GetRotation().x == 270 || activeCenter->GetRotation().x == 360)
				//activeCenter->GetRotation().y == 0 || activeCenter->GetRotation().y == 90 || activeCenter->GetRotation().y == 180 || activeCenter->GetRotation().y == 270 || activeCenter->GetRotation().y == 360 ||
				//activeCenter->GetRotation().z == 0 || activeCenter->GetRotation().z == 90 || activeCenter->GetRotation().z == 180 || activeCenter->GetRotation().z == 270 || activeCenter->GetRotation().z == 360)
			{
			*/
				rotating = false;
				activeCenter = NULL;
			//}
		}
		else
		{
			std::cout << "activeCenter is NULL" << endl;
		}
		
	}
}

void RubiksCubeCore::RotateSide()
{
	//Switch on the side that should be rotating
	switch (rotatingSide)
	{
	case 1:
		//Check to see if an active center has already been declared
		if (!activeCenter)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(1))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oTopBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oTopBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.y += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					oTopBlocks[i]->mTransform.position = Vector3D((cos(1.5f) * (oTopBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(1.5f) * (oTopBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.x),
						oTopBlocks[i]->mTransform.position.y,
						(sin(1.5f) * (oTopBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(1.5f) * (oTopBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oTopBlocks[i]->mTransform.rotation.y += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oTopBlocks.size(); i++)
			{
				if (oTopBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.y -= 4.0f;
				}
				else
				{
					oTopBlocks[i]->mTransform.position = Vector3D((cos(-1.5f) * (oTopBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(-1.5f) * (oTopBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.x),
						oTopBlocks[i]->mTransform.position.y,
						(sin(-1.5f) * (oTopBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(-1.5f) * (oTopBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oTopBlocks[i]->mTransform.rotation.y -= 4.0f;
				}
			}
		}
		break;

	case 2:
		//Check to see if an active center has already been declared
		if (!activeCenter)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(2))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oBottomBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oBottomBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.y += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					oBottomBlocks[i]->mTransform.position = Vector3D(
						(cos(1.5f) * (oBottomBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(1.5f) * (oBottomBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.x),
						oBottomBlocks[i]->mTransform.position.y,
						(sin(1.5f) * (oBottomBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(1.5f) * (oBottomBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oBottomBlocks[i]->mTransform.rotation.y += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oBottomBlocks.size(); i++)
			{
				if (oBottomBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.y -= 4.0f;
				}
				else
				{
					oBottomBlocks[i]->mTransform.position = Vector3D(
						(cos(-1.5f) * (oBottomBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(-1.5f) * (oBottomBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.x),
						oBottomBlocks[i]->mTransform.position.y,
						(sin(-1.5f) * (oBottomBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(-1.5f) * (oBottomBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oBottomBlocks[i]->mTransform.rotation.y -= 4.0f;
				}
			}
		}
		break;

	case 3:
		//Check to see if an active center has already been declared
		if (!activeCenter)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(3))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oFrontBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oFrontBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.z += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					oFrontBlocks[i]->mTransform.position = Vector3D(
						(cos(-1.5f) * (oFrontBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(-1.5f) * (oFrontBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.x),
						(sin(-1.5f) * (oFrontBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(-1.5f) * (oFrontBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.y),
						oFrontBlocks[i]->mTransform.position.z);

					oFrontBlocks[i]->mTransform.rotation.z += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oFrontBlocks.size(); i++)
			{
				if (oFrontBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.z -= 4.0f;
				}
				else
				{
					oFrontBlocks[i]->mTransform.position = Vector3D(
						(cos(1.5f) * (oFrontBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(1.5f) * (oFrontBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.x),
						(sin(1.5f) * (oFrontBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(1.5f) * (oFrontBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.y),
						oFrontBlocks[i]->mTransform.position.z);

					oFrontBlocks[i]->mTransform.rotation.z -= 4.0f;
				}
			}
		}
		break;

	case 4:
		//Check to see if an active center has already been declared
		if (!activeCenter)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(4))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oBackBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oBackBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.z += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					oBackBlocks[i]->mTransform.position = Vector3D(
						(cos(1.5f) * (oBackBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(1.5f) * (oBackBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.x),
						(sin(1.5f) * (oBackBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(1.5f) * (oBackBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.y),
						oBackBlocks[i]->mTransform.position.z);

					oBackBlocks[i]->mTransform.rotation.z += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oBackBlocks.size(); i++)
			{
				if (oBackBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.z -= 4.0f;
				}
				else
				{
					oBackBlocks[i]->mTransform.position = Vector3D(
						(cos(1.5f) * (oBackBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) - sin(1.5f) * (oBackBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.x),
						(sin(1.5f) * (oBackBlocks[i]->mTransform.position.x - activeCenter->mTransform.position.x) + cos(1.5f) * (oBackBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + activeCenter->mTransform.position.y),
						oBackBlocks[i]->mTransform.position.z);

					oBackBlocks[i]->mTransform.rotation.z -= 4.0f;
				}
			}
		}
		break;

	case 5:
		//Check to see if an active center has already been declared
		if (!activeCenter)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(5))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oRightBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oRightBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.x += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					oRightBlocks[i]->mTransform.position = Vector3D(oRightBlocks[i]->mTransform.position.x,
						(cos(-1.5f) * (oRightBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) - sin(-1.5f) * (oRightBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.y),
						(sin(-1.5f) * (oRightBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + cos(-1.5f) * (oRightBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oRightBlocks[i]->mTransform.rotation.x += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oRightBlocks.size(); i++)
			{
				if (oRightBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.x -= 4.0f;
				}
				else
				{
					oRightBlocks[i]->mTransform.position = Vector3D(oRightBlocks[i]->mTransform.position.x,
						(cos(1.5f) * (oRightBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) - sin(1.5f) * (oRightBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.y),
						(sin(1.5f) * (oRightBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + cos(1.5f) * (oRightBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oRightBlocks[i]->mTransform.rotation.x -= 4.0f;
				}
			}
		}
		break;

	case 6:
		//Check to see if an active center has already been declared
		if (activeCenter == NULL)
		{
			for (unsigned int i = 0; i < oCenterBlocks.size(); i++)
			{
				if (oCenterBlocks[i]->CheckForSide(6))
				{
					activeCenter = oCenterBlocks[i];
				}
			}
		}

		//Is the rotating positive or negative
		if (positive)
		{
			for (unsigned int i = 0; i < oLeftBlocks.size(); i++)
			{
				//Is the current block the activeCenter?
				if (oLeftBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.x += 4.0f;
				}
				else
				{
					//Rotate every other block around the center position
					
					oLeftBlocks[i]->mTransform.position = Vector3D(oLeftBlocks[i]->mTransform.position.x,
						(cos(-1.5f) * (oLeftBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) - sin(-1.5f) * (oLeftBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.y),
						(sin(-1.5f) * (oLeftBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + cos(-1.5f) * (oLeftBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));
					
					oLeftBlocks[i]->mTransform.rotation.x += 4.0f;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < oLeftBlocks.size(); i++)
			{
				if (oLeftBlocks[i] == activeCenter)
				{
					activeCenter->mTransform.rotation.x -= 4.0f;
				}
				else
				{
					oLeftBlocks[i]->mTransform.position = Vector3D(oLeftBlocks[i]->mTransform.position.x,
						(cos(1.5f) * (oLeftBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) - sin(1.5f) * (oLeftBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.y),
						(sin(1.5f) * (oLeftBlocks[i]->mTransform.position.y - activeCenter->mTransform.position.y) + cos(1.5f) * (oLeftBlocks[i]->mTransform.position.z - activeCenter->mTransform.position.z) + activeCenter->mTransform.position.z));

					oLeftBlocks[i]->mTransform.rotation.x -= 4.0f;
				}
			}
		}
		break;
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