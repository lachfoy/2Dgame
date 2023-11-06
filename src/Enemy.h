#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Metal.h"

class Input;
class Player;

class Enemy : public SpriteEntity
{
public:
	Enemy(glm::vec2 position, Player* player);
	~Enemy() {}

	void Damage(int amount);
	int GetDamage() const { return rand() % (m_maxDamage - m_minDamage + 1) + m_minDamage; }

	void Think();
	void Update(float dt);

	void OnRemove(std::vector<std::unique_ptr<Metal>>& metal);

private:
	glm::vec2 m_moveDir{ 0.0f };
	
	float m_acceleration = 400.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 8.f;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

	int m_maxHealth = 10;
	int m_health = m_maxHealth;

	int m_minDamage = 1;
	int m_maxDamage = 5;

	Player* m_player;

};