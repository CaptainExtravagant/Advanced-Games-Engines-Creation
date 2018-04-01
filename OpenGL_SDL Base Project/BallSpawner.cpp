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
			this, "Ball.obj", "OrangeBall.raw"));
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
				this, "Ball.obj", "OrangeBall.raw"));
		}
	}

	for (int i = 0; i < activeBalls.size(); i++)
	{
		activeBalls[i]->Update(deltaTime, e);
	}
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