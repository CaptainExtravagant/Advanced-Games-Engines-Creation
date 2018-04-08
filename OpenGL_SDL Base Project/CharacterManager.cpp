#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	SpawnPlayers();
	SpawnEnemies();
}

CharacterManager::~CharacterManager()
{

}

void CharacterManager::Update(float deltaTime, SDL_Event e)
{
	for (int i = 0; i < lPlayers.size(); i++)
	{
		lPlayers[i]->Update(deltaTime, e);
	}
	for (int i = 0; i < lEnemies.size(); i++)
	{
		lEnemies[i]->Update(deltaTime, e);
	}
}

void CharacterManager::Render()
{
	for (int i = 0; i < lPlayers.size(); i++)
	{
		lPlayers[i]->Render();
	}
	for (int i = 0; i < lEnemies.size(); i++)
	{
		lEnemies[i]->Render();
	}
}

void CharacterManager::SpawnEnemies()
{
	for (int i = 0; i < 5; i++)
	{
		lEnemies.push_back(new Level2Enemy(Vector3D(2*i, 2, 10), "Ball.obj", "OrangeBall.raw", 1, this));
	}
}

void CharacterManager::SpawnPlayers()
{
	lPlayers.push_back(new Level2Player(0, Vector3D(-10, 2, 0), "Ball.obj", "GreenBall.raw", this));
}

void CharacterManager::EnemyKilled(Level2Enemy* killed)
{

}