#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include "Enemy.h"

class DebugRenderer;

class EnemySpawner
{
public:
	EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies, DebugRenderer* debugRenderer) {}
	~EnemySpawner() {}

	void Update(float dt);

	void SpawnEnemy();

	std::vector<std::unique_ptr<Enemy>>* m_enemies;
	DebugRenderer* m_debugRenderer;

private:
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 0.5f; // make this more smart later on. Follow a defined curve.

	float m_elapsedTime = 0.0f;

};
