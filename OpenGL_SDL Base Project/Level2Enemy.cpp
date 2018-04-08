#include "Level2Enemy.h"
#include "CharacterManager.h"
#include "Level2Player.h"

#include <iostream>

Level2Enemy::Level2Enemy(Vector3D startPosition, string modelName, string textureName, int type, CharacterManager* manager) : GameObject(startPosition, modelName, textureName)
{
	mManager = manager;

	box = new Box(mTransform.position, 2, 2, 2, this);
	components.push_back(box);
}

Level2Enemy::~Level2Enemy()
{

}

void Level2Enemy::Update(float deltaTime, SDL_Event e)
{
	box->Update(mTransform.position);
}

void Level2Enemy::Hit(int damageType, float damageValue)
{
	cout << "Enemy Hit" << endl;
	mTransform.position.z += 1;

	currentHealth -= damageValue;
	if (currentHealth <= 0)
	{
		cout << "Enemy Killed" << endl;
		mManager->EnemyKilled(this);
	}
}

void Level2Enemy::FindTarget()
{

}

void Level2Enemy::MoveToTarget(float deltaTime)
{

}