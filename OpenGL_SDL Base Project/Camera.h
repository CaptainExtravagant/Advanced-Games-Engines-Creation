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
	void Render(GameObject* targetObject);
	void Render(Vector3D targetPosition);

	void SetMovementEnabled(bool enabled);
	bool GetMovementEnabled();
	void SetPosition(Vector3D pos);
	void SetYaw(float yaw);
	void SetPitch(float pitch);

private:
	bool movementEnabled = true;

	Vector3D position = Vector3D(5, 10, 20);
	Vector3D forward = Vector3D();
	Vector3D up = Vector3D();
	Vector3D right = Vector3D();

	//horizontal angle: toward -Z
	float yaw = 3.14f;
	//vertical angle: 0, look at the horizon; 90, look down
	float pitch = 0.0f;
};

#endif