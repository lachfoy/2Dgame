#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include "Enemy.h"

class Player;

class EnemySpawner
{
public:
	EnemySpawner(std::vector<Enemy*>& enemies, Player* player, std::vector<Turret*>& turrets);
	~EnemySpawner() {}

	void Update(float dt);

	void SpawnEnemyGroup();

private:
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 2.0f; // make this more smart later on. Follow a defined curve.

	float m_spawnRadius = 200.0f;

	//float m_elapsedTime = 0.0f;

	int m_enemiesPerGroup = 5;

	Player* m_player;

	std::vector<Enemy*>& m_enemies;

	std::vector<Turret*>& m_turrets;

};
