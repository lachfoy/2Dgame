#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include "Enemy.h"

class DebugRenderer;
class Renderer;
class Texture;
class Player;
class TextureManager;

class EnemySpawner
{
public:
	EnemySpawner(std::vector<std::unique_ptr<Enemy>>* enemies, DebugRenderer* debugRenderer, Player* player);
	~EnemySpawner() {}

	void Update(float dt, Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager);

	void SpawnEnemyGroup(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager);

private:
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 2.0f; // make this more smart later on. Follow a defined curve.

	float m_spawnRadius = 200.0f;

	//float m_elapsedTime = 0.0f;

	int m_enemiesPerGroup = 5;

	Player* m_player;

	std::vector<std::unique_ptr<Enemy>>* m_enemies;
	DebugRenderer* m_debugRenderer;

};
