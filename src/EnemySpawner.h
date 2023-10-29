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

	std::vector<std::unique_ptr<Enemy>>* m_enemies;
	DebugRenderer* m_debugRenderer;

};
