#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;

class Player : public SpriteEntity
{
public:
	Player(Renderer* renderer, Texture* texture) : SpriteEntity(renderer, texture, glm::ivec2(34, 54)) {}
	~Player() {}

	void HandleInput(Input* input);
	void Update(float dt);

private:
	glm::vec2 m_moveDir{ 0 };
	float m_moveSpeed = 300.0f;

};