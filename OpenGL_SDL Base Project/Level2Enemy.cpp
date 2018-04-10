#include "Level2Enemy.h"
#include "CharacterManager.h"
#include "Level2Player.h"

#include <iostream>

Level2Enemy::Level2Enemy(Vector3D startPosition, string modelName, string textureName, int type, CharacterManager* manager) : GameObject(startPosition, modelName, textureName)
{
	mManager = manager;

	box = new Box(mTransform.position, 2, 2, 2, this);
	components.push_back(box);

	SetScale(Vector3D(5, 5, 5));

	currentState = AI_SEARCHING;
}

Level2Enemy::~Level2Enemy()
{

}

void Level2Enemy::Update(float deltaTime, SDL_Event e)
{
	box->Update(mTransform.position);

	switch (currentState)
	{
	case AI_SEARCHING:
		if (FindTarget())
			currentState = AI_MOVING;
		break;

	case AI_MOVING:
		if (MoveToTarget(deltaTime))
			currentState = AI_SEARCHING;
	}
}

void Level2Enemy::Hit(int damageType, float damageValue, Level2Player* player)
{
	cout << "Enemy Hit" << endl;
	//mTransform.position.z += 1;
	mTransform.position -= (player->GetPosition() - mTransform.position).Normalise();

	currentHealth -= damageValue;
	if (currentHealth <= 0)
	{
		cout << "Enemy Killed" << endl;
		mManager->EnemyKilled(this);
	}
}

bool Level2Enemy::FindTarget()
{
	for (int i = 0; i < mManager->GetPlayers().size(); i++)
	{
		if (!targetSet)
		{
			targetSet = true;
			target = mManager->GetPlayers()[i];
			targetPosition = target->GetPosition();
			distanceToTarget = (mTransform.position - targetPosition).Magnitude();
		}
		else if ((mTransform.position - mManager->GetPlayers()[i]->GetPosition()).Magnitude() < distanceToTarget)
		{
			targetSet = true;
			target = mManager->GetPlayers()[i];
			targetPosition = target->GetPosition();
			distanceToTarget = (mTransform.position - targetPosition).Magnitude();
		}
	}

	return targetSet;
}

bool Level2Enemy::MoveToTarget(float deltaTime)
{
	if (target != NULL)
	{
		mTransform.AddPosition((target->GetPosition() - mTransform.position).Normalise() * deltaTime);
		if ((mTransform.position - target->GetPosition()).Magnitude() <= attackRange)
		{
			if (Collision::SphereBoxCollision(target->GetBoundingSphere(), box))
			{
				AttackTarget();
				targetSet = false;
				target = NULL;
				return true;
			}
		}
	}

	return false;
}

void Level2Enemy::AttackTarget()
{
	target->Hit();
}