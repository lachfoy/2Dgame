#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Input;
class Player;

class Enemy : public SpriteEntity
{
public:
	Enemy(Renderer* renderer, Texture* texture, Player* player);
	~Enemy() {}

	void Think();
	void Update(float dt);

private:
	glm::vec2 m_moveDir{ 0.0f };
	
	float m_acceleration = 1000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;

	Player* m_player;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

};