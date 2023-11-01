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

	void SpawnWave(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture, Player* player, TextureManager* textureManager);

private:
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 0.5f; // make this more smart later on. Follow a defined curve.

	float m_elapsedTime = 0.0f;

	Player* m_player;

	std::vector<std::unique_ptr<Enemy>>* m_enemies;
	DebugRenderer* m_debugRenderer;

};
