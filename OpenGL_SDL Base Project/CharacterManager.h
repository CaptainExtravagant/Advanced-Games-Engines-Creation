#ifndef CHARACTER_MANAGER
#define CHARACTER_MANAGER

#include "Level2Enemy.h"
#include "Level2Player.h"
#include "SoundEffect.h"

class GameScreenLevel2;

class CharacterManager {
public:
	CharacterManager(GameScreenLevel2* level);
	~CharacterManager();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void EnemyKilled(Level2Enemy* killed);
	void PlayerKilled(Level2Player* killed);

	vector<Level2Enemy*> GetEnemies() { return lEnemies; }
	vector<Level2Player*> GetPlayers() { return lPlayers; }

private:
	float mCurrentTime = 0;

	vector<Level2Enemy*> lEnemies;
	vector<Level2Player*> lPlayers;

	SoundEffect* mPlayerSound;
	SoundEffect* mZombieSound;

	GameScreenLevel2* mCurrentLevel;

	int RandomFloatInRange(int min, int max)
	{
		int outcome = rand() % ((max - min) + 1) + (min);

		return outcome;
	}

	void SpawnPlayers();
	void SpawnEnemies();
};

#endif