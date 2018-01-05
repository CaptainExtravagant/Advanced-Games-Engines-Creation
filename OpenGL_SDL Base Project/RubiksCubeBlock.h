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

	void DrawCube();
	
	virtual void SetPosition();
	GameObject* blockCore;

private:
	int activeSide;

	Vector3D xAxis = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D yAxis = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D zAxis = Vector3D(0.0f, 0.0f, 1.0f);

	float xAngle;
	float yAngle;
	float zAngle;
};


#endif