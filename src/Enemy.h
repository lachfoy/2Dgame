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

	void Update(float dt);

private:
	/*glm::vec2 m_moveDir{ 0.0f };
	float m_acceleration = 20000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;
	float kMaxSpeed = 400.0f;*/
	Player* m_player;

	float m_moveSpeed = 50.0f;

};