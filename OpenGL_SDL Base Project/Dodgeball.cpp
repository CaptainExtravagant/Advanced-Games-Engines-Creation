#include "Dodgeball.h"
#include "BallSpawner.h"

Dodgeball::Dodgeball(Vector3D startPosition, Vector3D startVelocity, BallSpawner* spawner, string modelName, string textureName) : GameObject(startPosition, modelName, textureName)
{
	rigidBody = new RigidBody(this);

	components.push_back(rigidBody);

	rigidBody->velocity = startVelocity;
	mSpawner = spawner;
}

Dodgeball::~Dodgeball()
{

}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	rigidBody->Update(deltaTime, e);

	if (rigidBody->velocity.Magnitude() <= 0.1f)
	{
		mSpawner->RemoveBall(this);
		return;
	}

	if (mTransform.position.x <= -11 || mTransform.position.x >= 11)
	{
		mSpawner->RemoveBall(this);
		return;
	}

	if (mTransform.position.z <= -7 || mTransform.position.z >= 7)
	{
		mSpawner->RemoveBall(this);
		return;
	}
}