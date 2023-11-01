#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Enemy.h"

class Turret : public SpriteEntity
{
public:
	Turret(Renderer* renderer, DebugRenderer* debugRenderer, glm::vec2 position, Texture* texture, std::vector<std::unique_ptr<Enemy>>* enemies);
	~Turret() {}

	void Think(); // exact same as enemy
	void Update(float dt);

private:
	std::vector<std::unique_ptr<Enemy>>* m_enemies;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

};