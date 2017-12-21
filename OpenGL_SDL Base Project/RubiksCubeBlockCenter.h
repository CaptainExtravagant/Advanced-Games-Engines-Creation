#ifndef _RUBIKSCUBE_BLOCK_CENTER
#define _RUBIKSCUBE_BLOCK_CENTER
#include "RubiksCubeBlock.h"

class RubiksCubeBlockCenter : public RubiksCubeBlock
{
public:
	RubiksCubeBlockCenter(int newSide);
	~RubiksCubeBlockCenter();
	
	bool CheckForSide(int sideSelection);

private:
	void SetRotation();
	void SetPosition();

	int activeSide;
};

#endif