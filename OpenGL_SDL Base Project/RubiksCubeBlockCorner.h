#ifndef _RUBIKSCUBE_BLOCK_CORNER
#define _RUBIKSCUBE_BLOCK_CORNER
#include "RubiksCubeBlock.h"

class RubiksCubeBlockCorner : public RubiksCubeBlock
{
public:
	RubiksCubeBlockCorner(int side1, int side2, int side3);
	~RubiksCubeBlockCorner();

	bool CheckForSide(int sideSelection);
	void AssignSides(int side1, int side2, int side3);

private:
	void SetRotation();
	void SetPosition();

	vector<int> activeSides;
};


#endif