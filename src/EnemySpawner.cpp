#include "EnemySpawner.h"

#include "Player.h"

#define M_PI 3.14159265358979323846

EnemySpawner::EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies, DebugRenderer* debugRenderer, Player* player)
	: m_enemies(enemies), m_debugRenderer(debugRenderer), m_player(player)
{
}

void EnemySpawner::Update(float dt, Renderer* renderer, DebugRenderer* debugRenderer, Player* player, TextureManager* textureManager)
{
	//m_elapsedTime += dt;
	m_spawnTimer += dt;

	if (m_spawnTimer >= m_spawnInterval)
	{
		SpawnEnemyGroup(renderer, debugRenderer, player, textureManager);
		m_spawnTimer = 0.0f; // Reset
	}
}

void EnemySpawner::SpawnEnemyGroup(Renderer* renderer, DebugRenderer* debugRenderer, Player* player, TextureManager* textureManager)
{
	glm::vec2 playerPos = m_player->GetPosition();

	for (int i = 0; i < m_enemiesPerGroup; i++)
	{
		float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
		glm::vec2 spawnPos = playerPos + glm::vec2(std::cos(randomAngle), std::sin(randomAngle)) * m_spawnRadius;

		m_enemies->push_back(std::make_unique<Enemy>(renderer, debugRenderer, textureManager, spawnPos, m_player));
	}
}
