#ifndef _RUBIKSCUBE_CORE
#define _RUBIKECUBE_CORE
#include "GameObject.h"
#include "RubiksCubeBlock.h"
#include "RubiksCubeBlockEdge.h"
#include "RubiksCubeBlockCorner.h"
#include "RubiksCubeBlockCenter.h"

class RubiksCubeCore : public GameObject
{
public:
	RubiksCubeCore();
	~RubiksCubeCore();

	void Rotate(Vector3D rotateDirection);

	void UpdateSides(GameObject* rotatedSide);

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:

	void SpawnBlocks();

	vector<RubiksCubeBlock*> oBlockList;

	vector<RubiksCubeBlock*> oTopBlocks;
	vector<RubiksCubeBlock*> oBottomBlocks;
	vector<RubiksCubeBlock*> oBackBlocks;
	vector<RubiksCubeBlock*> oFrontBlocks;
	vector<RubiksCubeBlock*> oLeftBlocks;
	vector<RubiksCubeBlock*> oRightBlocks;
};

#endif