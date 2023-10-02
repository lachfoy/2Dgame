#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;
struct GameState;

class Player : public SpriteEntity
{
public:
	Player(Renderer* renderer, Texture* texture, GameState* gameState);
	~Player() {}

	void HandleInput(Input* input);
	void Update(float dt);

private:
	glm::vec2 m_moveDir{ 0.0f };
	float m_acceleration = 20000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;
	float kMaxSpeed = 400.0f;
	GameState* m_gameState;

	//int m_laneIndex;

	//float m_desiredX;
	//float m_lerpRate = 40.0f;

};