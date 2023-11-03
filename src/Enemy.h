#pragma once

#include "SpriteEntity.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Metal.h"
#include "Player.h"

class Input;
class TextureManager;

class Enemy : public SpriteEntity
{
public:
	Enemy(Renderer* renderer, DebugRenderer* debugRenderer, glm::vec2 position, Texture* texture, TextureManager* textureManager);
	~Enemy() {}

	void Damage(int amount);
	int GetDamage() const { return rand() % (m_maxDamage - m_minDamage + 1) + m_minDamage; }

	void Think(const Player& player);
	void Update(float dt, const Player& player);

	void OnRemove(std::vector<std::unique_ptr<Metal>>& metal);

private:
	glm::vec2 m_moveDir{ 0.0f };
	
	float m_acceleration = 1000.0f;

	glm::vec2 m_velocity{ 0.0f };
	float kFrictionCoef = 0.5f;

	float m_thinkTimer = 0.0f;
	const float kThinkInterval = 0.5f;

	TextureManager* m_textureManager;

	int m_maxHealth = 10;
	int m_health = m_maxHealth;

	int m_minDamage = 1;
	int m_maxDamage = 5;

};