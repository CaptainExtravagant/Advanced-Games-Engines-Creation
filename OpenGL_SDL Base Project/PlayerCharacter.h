#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "GameObject.h"
#include "Collision.h"
#include "SoundEffect.h"
#include <math.h>

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter(Vector3D startPosition, string modelFileName, string textureFileName);
	~PlayerCharacter();

	void Update(float deltaTime, SDL_Event e);

	Sphere* sphere;

	Sphere* GetBoundingSphere() { return sphere; }

	void HitBall();

	int GetHits() { return hits; }

private:

	Vector2D stickInput;
	SDL_GameController* mController;
	int controllerIndex = 0;

	float movement;
	float xDir = 0;
	float yDir = 0;

	int hits;
};

#endif