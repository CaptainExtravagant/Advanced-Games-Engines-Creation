#ifndef DODGEBALL_H
#define DODGEBALL_H

#include "GameObject.h"
#include "RigidBody.h"

class BallSpawner;

class Dodgeball : public GameObject
{
public:
	Dodgeball(Vector3D startPosition, Vector3D startVelocity, BallSpawner* spawner, string modelName, string textureName);
	~Dodgeball();

	void Update(float deltaTime, SDL_Event e);

	RigidBody* rigidBody;

private:
	BallSpawner* mSpawner;
};

#endif
