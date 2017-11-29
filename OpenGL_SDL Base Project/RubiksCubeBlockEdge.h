#ifndef _RUBIKSCUBE_BLOCK_EDGE
#define _RUBIKSCUBE_BLOCK_EDGE
#include "GameObject.h"
#include "RubiksCubeBlock.h"

class RubiksCubeBlockEdge : public RubiksCubeBlock
{
public:
	RubiksCubeBlockEdge(int side1, int side2);
	~RubiksCubeBlockEdge();

	bool CheckForSide(int sideSelection);
	void AssignSides(int side1, int side2);

private:
	void SetRotation();
	void SetPosition();

	vector<int> activeSides;
};


#endif