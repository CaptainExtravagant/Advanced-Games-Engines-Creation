#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "GameObject.h"
#include "Collision.h"
#include "SoundEffect.h"

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

	float movement;

	int hits;
};

#endif