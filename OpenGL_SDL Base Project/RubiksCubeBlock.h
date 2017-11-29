#ifndef _RUBIKSCUBE_BLOCK
#define _RUBIKSCUBE_BLOCK
#include "Commons.h"
#include "GameObject.h"

class RubiksCubeBlock : public GameObject
{
public:
	RubiksCubeBlock();
	~RubiksCubeBlock();


protected:
	virtual void SetRotation();
	virtual void SetPosition();
	GameObject* blockCore;
};


#endif