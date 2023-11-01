#include "EnemySpawner.h"

void EnemySpawner::Update(float dt)
{
	m_elapsedTime += dt;

	

	m_spawnTimer += dt;
	if (m_spawnTimer >= m_spawnInterval)
	{
		SpawnEnemy();
		m_spawnTimer = 0.0f; // Reset
	}
}

void EnemySpawner::SpawnEnemy()
{

	//m_enemies->push_back(std::make_unique<Enemy>());
}
