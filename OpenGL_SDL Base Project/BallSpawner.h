#ifndef BALL_SPAWNER_H
#define BALL_SPAWNER_H

#include "Commons.h"
#include "Dodgeball.h"
#include <vector>

class BallSpawner
{
public:
	BallSpawner();
	~BallSpawner();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void RemoveBall(Dodgeball* ball);

private:
	vector<Dodgeball*>activeBalls;
	int ballLimit = 6;
	
	float RandomFloatInRange(int min, int max)
	{
		float outcome = rand() % ((max - min) + 1) + (min);

		return outcome;
	}
};

#endif