#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include "GameObject.h"
#include <SDL.h>

class Camera
{
public:
	Camera();
	~Camera();
	static Camera* GetInstance();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void Render(GameObject targetObject);

private:
	Vector3D position = Vector3D(0, 0, 10);
	Vector3D forward = Vector3D();
	Vector3D up = Vector3D();
	Vector3D right = Vector3D();

	//horizontal angle: toward -Z
	float yaw = 3.14f;
	//vertical angle: 0, look at the horizon
	float pitch = 0.0f;
};

#endif