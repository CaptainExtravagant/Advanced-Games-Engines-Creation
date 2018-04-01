#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "GameObject.h"

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter(Vector3D startPosition, string modelFileName, string textureFileName);
	~PlayerCharacter();

	void Update(float deltaTime, SDL_Event e);

private:
	float movement;
};

#endif