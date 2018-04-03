#include "Dodgeball.h"
#include "BallSpawner.h"

Dodgeball::Dodgeball(Vector3D startPosition, Vector3D startVelocity, string modelName, string textureName) : GameObject(startPosition, modelName, textureName)
{
	rigidBody = new RigidBody(this);
	sphere = new Sphere(mTransform.position, 1.7f, this);
	//sphere->SetCollided(false, NULL);
	mSound = new SoundEffect();
	mSound->LoadClip("Bounce.wav");

	components.push_back(rigidBody);
	components.push_back(sphere);

	rigidBody->velocity = startVelocity;
}

Dodgeball::~Dodgeball()
{

}

void Dodgeball::Update(float deltaTime, SDL_Event e)
{
	//if (sphere->GetCollided())
	//{
	//	rigidBody->Bounce(sphere->GetCollidedObject());
	//}

	rigidBody->Update(deltaTime, e);
	if (mTransform.position.y <= 2.0f)
	{
		mSound->Play();
	}

	sphere->SetCollided(false, NULL);
	sphere->Update(mTransform.position);

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