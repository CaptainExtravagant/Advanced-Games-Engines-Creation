#ifndef DODGEBALL_H
#define DODGEBALL_H

#include "GameObject.h"
#include "RigidBody.h"
#include "Collision.h"
#include "SoundEffect.h"

class BallSpawner;

class Dodgeball : public GameObject
{
public:
	Dodgeball(Vector3D startPosition, Vector3D startVelocity, string modelName, string textureName);
	~Dodgeball();

	void Update(float deltaTime, SDL_Event e);

	RigidBody* rigidBody;
	Sphere* sphere;

	Sphere* GetBoundingSphere() { return sphere; }
	void SetSpawner(BallSpawner* spawner) { mSpawner = spawner; }

private:
	BallSpawner* mSpawner;
	SoundEffect* mSound;
};

#endif
