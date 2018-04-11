#ifndef LEVEL2_PLAYER
#define LEVEL2_PLAYER

#include "GameObject.h"
#include "Collision.h"
#include <math.h>
#include "SoundEffect.h"

class CharacterManager;
class Level2Enemy;

class Level2Player : public GameObject
{
public:
	Level2Player(int playerIndex, Vector3D startPosition, string modelName, string textureName, CharacterManager* manager);
	~Level2Player();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	Sphere* GetBoundingSphere() { return sphere; }
	int GetWeaponType() { return activeWeapon; }

	void Hit();

private:
	CharacterManager* mManager;

	void FireWeapon(float deltaTime);
	void ChangeWeapon(int type);

	int controllerIndex;
	SDL_GameController* mController = NULL;
	float movement;
	Sphere* sphere;

	float xDir = 0;
	float yDir = 0;
	Vector2D stickInput;

	Vector2D lookInput;
	float xLook = 0;
	float yLook = 0;
	float lookAngle = 0;

	int activeWeapon = 1;
	float weaponRange = 20;
	Vector3D fireEnd;
	float fireTimer = 0.2f;
	bool fireReady = true;
	SoundEffect* mGunshotSound;
	SoundEffect* mScreamSound;

	bool debug = true;
};

#endif