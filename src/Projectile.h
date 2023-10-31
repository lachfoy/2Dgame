#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Enemy.h"

class Projectile : public SpriteEntity
{
public:
	Projectile(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture);
	~Projectile() {}

	void Update(float dt);

private:
	
	glm::vec2 m_moveDir{0.0f};
	float m_moveSpeed = 20.0f;

};