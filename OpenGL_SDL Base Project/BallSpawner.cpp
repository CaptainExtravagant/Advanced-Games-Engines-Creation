#include "BallSpawner.h"

BallSpawner::BallSpawner()
{
	for (int i = 0; i < ballLimit; i++)
	{
		activeBalls.push_back(new Dodgeball(
			Vector3D(RandomFloatInRange(-10, 10),
				10,
				RandomFloatInRange(-6, 6)),
			Vector3D(RandomFloatInRange(-1, 1),
				RandomFloatInRange(-10, -2),
				RandomFloatInRange(-1, 1)),
			"Ball.obj", "OrangeBall.raw"));
		activeBalls.back()->SetSpawner(this);
	}
}

BallSpawner::~BallSpawner()
{

}

void BallSpawner::Update(float deltaTime, SDL_Event e)
{
	if (activeBalls.size() < ballLimit)
	{
		for (int i = 0; i < activeBalls.size() - ballLimit; i++)
		{
			activeBalls.push_back(new Dodgeball(
				Vector3D(RandomFloatInRange(-10, 10),
					10,
					RandomFloatInRange(-6, 6)),
				Vector3D(RandomFloatInRange(-1, 1),
					RandomFloatInRange(-10, -2),
					RandomFloatInRange(-1, 1)),
				"Ball.obj", "OrangeBall.raw"));
			activeBalls.back()->SetSpawner(this);
		}
	}

	for (int i = 0; i < activeBalls.size(); i++)
	{
		activeBalls[i]->Update(deltaTime, e);
	}

	// check for collisions
	for (int i = 0; i < activeBalls.size() - 1; i++) {
		for (int j = i + 1; j < activeBalls.size(); j++) {
			Collision::SphereSphereCollision(activeBalls[i]->GetBoundingSphere(), activeBalls[j]->GetBoundingSphere());
		}
	}
}

bool BallSpawner::CheckPlayerCollision(PlayerCharacter* player)
{
	for (int i = 0; i < activeBalls.size(); i++)
	{
		if (Collision::SphereSphereCollision(activeBalls[i]->GetBoundingSphere(), player->GetBoundingSphere()))
		{
			activeBalls[i]->SetPosition(Vector3D(activeBalls[i]->GetPosition().x, 2, activeBalls[i]->GetPosition().z));
			activeBalls[i]->GetBoundingSphere()->SetEnabled(false);
			return true;
		}
	}

	return false;
}

void BallSpawner::Render()
{
	for (int i = 0; i < activeBalls.size(); i++)
	{
		activeBalls[i]->Render();
	}
}

void BallSpawner::RemoveBall(Dodgeball* ball)
{
	activeBalls.erase(remove(activeBalls.begin(), activeBalls.end(), ball));
	delete ball;
}