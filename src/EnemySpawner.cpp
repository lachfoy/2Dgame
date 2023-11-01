#include "EnemySpawner.h"

#include "Player.h"
#include "SDL_stdinc.h"

EnemySpawner::EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies, DebugRenderer* debugRenderer, Player* player)
	: m_enemies(enemies), m_debugRenderer(debugRenderer), m_player(player)
{
}

void EnemySpawner::Update(float dt, Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager)
{
	m_elapsedTime += dt;

	m_spawnTimer += dt;
	if (m_spawnTimer >= m_spawnInterval)
	{

		SpawnWave(renderer, debugRenderer, texture, player, textureManager);

		m_spawnTimer = 0.0f; // Reset
	}
}

void EnemySpawner::SpawnWave(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager)
{
	glm::vec2 pos = m_player->GetPosition();

	const float radius = 50.0f;
	const int enemiesToSpawn = 10;

	for (int i = 0; i < enemiesToSpawn; i++)
	{
		float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;

		float x = std::cos(randomAngle);
		float y = std::sin(randomAngle);

		glm::vec2 spawnPos = pos + glm::vec2(x, y)* radius;

		m_enemies->push_back(std::make_unique<Enemy>(renderer, debugRenderer, spawnPos, texture, player, textureManager));
	}
}
