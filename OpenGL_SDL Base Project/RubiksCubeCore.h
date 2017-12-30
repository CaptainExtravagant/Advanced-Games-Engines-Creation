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
	
	void Update(float deltaTime, SDL_Event e);
	void Render();

private:

	void SpawnBlocks();
	void RotateSide();

	bool rotating;
	int rotatingSide;
	bool positive;
	RubiksCubeBlockCenter* activeCenter;

	vector<RubiksCubeBlock*> oBlockList;

	vector<RubiksCubeBlock*> oRotatingBlocks;

	vector<RubiksCubeBlockCenter*> oCenterBlocks;
	vector<RubiksCubeBlockCorner*> oCornerBlocks;
	vector<RubiksCubeBlockEdge*> oEdgeBlocks;

	vector<RubiksCubeBlock*> oTopBlocks;
	vector<RubiksCubeBlock*> oBottomBlocks;
	vector<RubiksCubeBlock*> oBackBlocks;
	vector<RubiksCubeBlock*> oFrontBlocks;
	vector<RubiksCubeBlock*> oLeftBlocks;
	vector<RubiksCubeBlock*> oRightBlocks;
};

#endif