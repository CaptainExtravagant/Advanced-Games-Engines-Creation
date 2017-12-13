#ifndef _RUBIKSCUBE_BLOCK
#define _RUBIKSCUBE_BLOCK
#include "Commons.h"
#include "GameObject.h"
#include <SDL.h>

class RubiksCubeBlock : public GameObject
{
public:
	RubiksCubeBlock();
	~RubiksCubeBlock();

	void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool CheckForSide(int sideToCheck);


protected:
	virtual void SetRotation();
	
	virtual void SetPosition();
	GameObject* blockCore;

private:
	int activeSide;
};


#endif