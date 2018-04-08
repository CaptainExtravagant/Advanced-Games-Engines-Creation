#ifndef CHARACTER_MANAGER
#define CHARACTER_MANAGER

#include "Level2Enemy.h"
#include "Level2Player.h"

class CharacterManager {
public:
	CharacterManager();
	~CharacterManager();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void EnemyKilled(Level2Enemy* killed);

	vector<Level2Enemy*> GetEnemies() { return lEnemies; }
	vector<Level2Player*> GetPlayers() { return lPlayers; }

private:
	vector<Level2Enemy*> lEnemies;
	vector<Level2Player*> lPlayers;

	void SpawnPlayers();
	void SpawnEnemies();
};

#endif