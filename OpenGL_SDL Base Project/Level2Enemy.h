#ifndef LEVEL2_ENEMY
#define LEVEL2_ENEMY

#include "GameObject.h"
#include "Collision.h"
#include <math.h>

class CharacterManager;
class Level2Player;

class Level2Enemy : public GameObject
{
public:
	Level2Enemy(Vector3D startPosition, string modelName, string textureName, int enemyType, CharacterManager* manager);
	~Level2Enemy();

	void Update(float deltaTime, SDL_Event e);

	Box* GetBoundingBox() { return box; }
	int GetEnemyType() { return type; }
	void Hit(int incomingDamage, float damageValue);
	Level2Player* GetTarget() { return target; }
	void TargetKilled() { target = NULL; targetSet = false; currentState = AI_SEARCHING; }

private:
	CharacterManager* mManager;
	Level2Player* target = NULL;

	float distanceToTarget = 0;
	Vector3D targetPosition;
	bool targetSet = false;

	enum AI_STATE {
		AI_SEARCHING = 0,
		AI_MOVING
	};

	AI_STATE currentState;

	bool FindTarget();
	bool MoveToTarget(float deltaTime);
	void AttackTarget();

	float movement = 4.0f;
	Box* box;
	int type;
	float maxHealth = 100;
	float currentHealth = maxHealth;

	float lookAngle = 0;
	float attackRange = 2.0f;
};

#endif