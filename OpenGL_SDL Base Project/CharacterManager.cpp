#include "CharacterManager.h"
#include "GameScreenLevel2.h"

CharacterManager::CharacterManager(GameScreenLevel2* level)
{
	mCurrentLevel = level;

	SpawnPlayers();
	SpawnEnemies();
}

CharacterManager::~CharacterManager()
{
	for (int i = 0; i < lEnemies.size(); i++)
	{
		delete lEnemies[i];
		lEnemies[i] = NULL;
	}
	for (int i = 0; i < lPlayers.size(); i++)
	{
		delete lPlayers[i];
		lPlayers[i] = NULL;
	}
}

void CharacterManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

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
	float spawnModifier = (mCurrentTime / 100 + 1) ;

	for (int i = 0; i < 5 * spawnModifier; i++)
	{
		switch (RandomFloatInRange(0, 3))
		{
		case 0:
			lEnemies.push_back(new Level2Enemy(Vector3D(RandomFloatInRange(-5, 5), 2, 13), "Ball.obj", "OrangeBall.raw", 1, this));
			break;
		case 1:
			lEnemies.push_back(new Level2Enemy(Vector3D(18, 2, RandomFloatInRange(-5, 5)), "Ball.obj", "OrangeBall.raw", 1, this));
			break;
		case 2:
			lEnemies.push_back(new Level2Enemy(Vector3D(RandomFloatInRange(-5, 5), 2, -13), "Ball.obj", "OrangeBall.raw", 1, this));
			break;
		case 3:
			lEnemies.push_back(new Level2Enemy(Vector3D(-18, 2, RandomFloatInRange(-5, 5)), "Ball.obj", "OrangeBall.raw", 1, this));
			break;
		}
	}
}

void CharacterManager::SpawnPlayers()
{
	for (int i = 0; i < 2; i++)
	{
		lPlayers.push_back(new Level2Player(i, Vector3D(10*i, 2, 0), "Ball.obj", "GreenBall.raw", this));
	}
}

void CharacterManager::EnemyKilled(Level2Enemy* killed)
{
	lEnemies.erase(remove(lEnemies.begin(), lEnemies.end(), killed));
	delete killed;

	mCurrentLevel->AddKill();

	if (lEnemies.size() <= 3)
	{
		SpawnEnemies();
	}
}

void CharacterManager::PlayerKilled(Level2Player* killed)
{
	lPlayers.erase(remove(lPlayers.begin(), lPlayers.end(), killed));
	for (int i = 0; i < lEnemies.size(); i++)
	{
		if (lEnemies[i]->GetTarget() == killed)
		{
			lEnemies[i]->TargetKilled();
		}
	}

	delete killed;

	if (lPlayers.size() <= 0)
	{
		mCurrentLevel->LostGame();
	}
}