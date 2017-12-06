#include "Camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 1.0f;
static float lookSpeed = 0.1f;

Camera::Camera()
{

}

Camera::~Camera()
{

}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	//Forward Vector: Spherical coordinates to Cartesian coordiantes conversion (also known as the 'look' direction)
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw));

	//Right Vector
	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	//Up vector: perpendicular to both forward and right, calculate using the cross product
	up = Vector3D((right.y*forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));

	//Event Handler
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			//move forwards
			position += forward * moveSpeed;
			break;

		case SDLK_s:
			//move backwards
			position -= forward * moveSpeed;
			break;

		case SDLK_d:
			//Strafe right
			position += right * moveSpeed;
			break;

		case SDLK_a:
			//Strafe left
			position -= right * moveSpeed;
			break;

		case SDLK_UP:
			//Look up
			pitch += lookSpeed;
			break;

		case SDLK_DOWN:
			//Look down
			pitch -= lookSpeed;
			break;

		case SDLK_LEFT:
			//Look left
			yaw += lookSpeed;
			break;

		case SDLK_RIGHT:
			//Look right
			yaw -= lookSpeed;
			break;
		}
	}
}

void Camera::Render()
{
	Vector3D lookatPos = position + forward; //Make sure we're always looking at a point in front of the camera
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);
}

void Camera::Render(GameObject targetObject)
{
	Vector3D lookatPos = targetObject.GetPosition();
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);
}