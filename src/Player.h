#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;

class Player : public SpriteEntity
{
public:
	Player(Renderer* renderer, DebugRenderer* debugRenderer, Texture* texture);
	~Player() {}

	void HandleInput(Input* input);
	void Update(float dt);

private:
	glm::vec2 m_moveDir{ 0.0f };
	float m_acceleration = 10000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;
	float kMaxSpeed = 400.0f;

};